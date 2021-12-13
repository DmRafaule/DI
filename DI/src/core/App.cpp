#include "App.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace DI{

   Scope<DI::AppData> _appData;
   Scope<DI::ImGUIData> _imguiData;
   extern Scope<DI::WinData> _winData;
   
   App::App(){
      Log::Init();
      DI_LOG_TRACE("Init App");
      _winData = C_Scope<WinData>();
      _appData = C_Scope<AppData>();
      _imguiData = C_Scope<ImGUIData>();
      WinHandler::WinInit(*_winData);
      WinHandler::ImGUIInit(*_winData);
   }
   App::~App(){
      SceneHandler::Clear();//HERE layers are not deleted
      WinHandler::ImGUIKill(*_winData);
      WinHandler::WinKill(*_winData);
      DI_LOG_TRACE("Kill App");
   }
   void App::run(){
      while(_winData->isOpen){
         CoreTime  Timer;
         SDL_Event Event;
         
         while (SDL_PollEvent(&Event)){
            switch (Event.type){
            case SDL_QUIT:{
               _winData->isOpen = false;
               break;
            }
            case SDL_WINDOWEVENT:{
               switch (Event.window.event){
               case SDL_WINDOWEVENT_RESIZED:{
                  _winData->size = glm::vec2(Event.window.data1,Event.window.data2);
                  glViewport(_winData->pos.x,_winData->pos.y,_winData->size.x,_winData->size.y);
                  EventsHandler::WinResized(_winData->size);
                  break;
               }
               case SDL_WINDOWEVENT_CLOSE:{
                  _winData->isOpen = false;
                  EventsHandler::WinClosed();
                  break;
               }
               case SDL_WINDOWEVENT_TAKE_FOCUS:{
                  _winData->isMinimized = false;
                  EventsHandler::WinFocused();
                  break;
               }
               case SDL_WINDOWEVENT_MOVED:{
                  _winData->pos = glm::vec2(Event.window.data1,Event.window.data2);
                  EventsHandler::WinMoved(_winData->pos);
                  break;
               }
               case SDL_WINDOWEVENT_MINIMIZED:{
                  _winData->isMinimized = true;
                  EventsHandler::WinMinimized();
                  break;
               }
               }
               break;
            }
            case SDL_KEYUP:{
               _appData->key = Event.key.keysym.sym;
               EventsHandler::KeyReleased(_appData->key);
               break;
            }
            case SDL_KEYDOWN:{
               _appData->key = Event.key.keysym.sym; 
               _appData->isKey_repeat = Event.key.repeat; 
               EventsHandler::KeyPressed(_appData->key, _appData->isKey_repeat);
               break;
            }
            case SDL_MOUSEMOTION:{
               _appData->mousePos = glm::vec2(Event.motion.x,Event.motion.y);
               EventsHandler::MouseMoved(_appData->mousePos);
               break;
            }
            case SDL_MOUSEWHEEL:{
               _appData->mouseWheelOffset = glm::vec2(Event.wheel.x,Event.wheel.y);
               EventsHandler::MouseScrolled(_appData->mouseWheelOffset);
               break;
            }
            case SDL_MOUSEBUTTONDOWN:{
               _appData->key = Event.key.keysym.sym;
               EventsHandler::MousePressed(Event.key.keysym.sym,0);
               break;
            }
            case SDL_MOUSEBUTTONUP:{
               _appData->key = Event.key.keysym.sym;
               EventsHandler::MouseReleased(_appData->key);
               break;
            }
            default:{
               break;
            }
            }
            EventsHandler::CustomEvent(Event);
            updateEvents_loop_ImGUI(Event);
         }
     
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
         glClearColor(_winData->bg.r,_winData->bg.g,_winData->bg.b, 1.0f );
         
         if (!_winData->isMinimized){
            SceneHandler::Update();
         }
         updateRender_loop_ImGUI();
      
         SDL_GL_SwapWindow(_winData->win);
         EventsHandler::AppFrameChanged();
      }
   }

   void App::updateEvents_loop_ImGUI(SDL_Event& event){
      if (_winData->isImGUI)
         ImGui_ImplSDL2_ProcessEvent(&event);
   }
   void App::updateRender_loop_ImGUI(){
      if (_winData->isImGUI){
         ImGui_ImplOpenGL3_NewFrame();
         ImGui_ImplSDL2_NewFrame();
         ImGui::NewFrame();
         ImGui::SetNextWindowPos( ImVec2(0,0) );
         ImGui::SetNextWindowSize( ImVec2(_winData->size.x * 0.2,_winData->size.y ) );
         ImGuiWindowFlags flags = (ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
         
         
         ImGui::Begin("Menu", &_winData->isImGUI,flags);

         ImGui::Text("Win pos:   %g %g",_winData->pos.x,_winData->pos.y);
         ImGui::Text("Win size:  %g %g",_winData->size.x,_winData->size.y);
         ImGui::Text("Mouse pos: %g %g",_appData->mousePos.x,_appData->mousePos.y);
         ImGui::Text("Time since start: %g",CoreTime::time_since_start_programm);
         ImGui::Text("FPS: %g",1 / CoreTime::tic);
         ImGui::Text("Planets");
         ImGui::SliderFloat3("dirLight pos",glm::value_ptr(_imguiData->pointPos),-100.0f,100.0f);
         ImGui::SliderFloat3("light pos",glm::value_ptr(_imguiData->pointPos),-100.0f,100.0f);   
         ImGui::SliderFloat3("ambient",glm::value_ptr(_imguiData->ambient),-100.0f,100.0f);
         ImGui::SliderFloat3("diffuse",glm::value_ptr(_imguiData->diffuse),-100.0f,100.0f);
         ImGui::SliderFloat3("specular",glm::value_ptr(_imguiData->specular),-100.0f,100.0f);
  
         ImGui::InputFloat("constant",&_imguiData->constant);
         ImGui::InputFloat("linear",&_imguiData->linear);
         ImGui::InputFloat("quadratic",&_imguiData->quadratic);

         ImGui::Text("Sol");
         ImGui::SliderFloat3("ambient_",glm::value_ptr(_imguiData->ambient_),-100.0f,100.0f);
         ImGui::SliderFloat3("diffuse_",glm::value_ptr(_imguiData->diffuse_),-100.0f,100.0f);
         ImGui::SliderFloat3("specular_",glm::value_ptr(_imguiData->specular_),-100.0f,100.0f);
  
         ImGui::InputFloat("constant_",&_imguiData->constant_);
         ImGui::InputFloat("linear_",&_imguiData->linear_);
         ImGui::InputFloat("quadratic_",&_imguiData->quadratic_);
         ImGui::InputFloat("shineness_",&_imguiData->shineness_);

         ImGui::End();

         // Rendering
         ImGui::Render();
         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      }
   }
};
