#include "App.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace DI{
   
   App::App(){
      Log::Init();
      DI_LOG_TRACE("Init App");
      WinHandler::WinInit(_winData);
      WinHandler::ImGUIInit(_winData);

   }
   App::~App(){
      WinHandler::ImGUIKill(_winData);
      WinHandler::WinKill(_winData);
      DI_LOG_TRACE("Kill App");
   }
   void App::run(){
      while(_winData.isOpen){
         CoreTime  Timer;
         SDL_Event Event;
         
         while (SDL_PollEvent(&Event)){
            switch (Event.type){
            case SDL_QUIT:{
               _winData.isOpen = false;
               break;
            }
            case SDL_WINDOWEVENT:{
               switch (Event.window.event){
               case SDL_WINDOWEVENT_RESIZED:{
                  _winData.size = glm::vec2(Event.window.data1,Event.window.data2);
                  onWinResized(_winData.size);
                  break;
               }
               case SDL_WINDOWEVENT_CLOSE:{
                  _winData.isOpen = false;
                  break;
               }
               case SDL_WINDOWEVENT_TAKE_FOCUS:{
                  onWinFocused();
                  break;
               }
               case SDL_WINDOWEVENT_MOVED:{
                  _winData.pos = glm::vec2(Event.window.data1,Event.window.data2);
                  onWinMoved(_winData.pos);
                  break;
               }
               }
               break;
            }
            case SDL_KEYUP:{
               _appData.key = Event.key.keysym.sym;
               onKeyReleased(_appData.key);
               break;
            }
            case SDL_KEYDOWN:{
               _appData.key = Event.key.keysym.sym; 
               _appData.isKey_repeat = Event.key.repeat; 
               onKeyPressed(_appData.key, _appData.isKey_repeat);
               break;
            }
            case SDL_MOUSEMOTION:{
               _appData.mousePos = glm::vec2(Event.motion.x,Event.motion.y);
               onMouseMoved(_appData.mousePos);
               break;
            }
            case SDL_MOUSEWHEEL:{
               _appData.mouseWheelOffset = glm::vec2(Event.wheel.x,Event.wheel.y);
               onMouseScrolled(_appData.mouseWheelOffset);
               break;
            }
            case SDL_MOUSEBUTTONDOWN:{
               _appData.key = Event.key.keysym.sym;
               onMousePressed(Event.key.keysym.sym,0);
               break;
            }
            case SDL_MOUSEBUTTONUP:{
               _appData.key = Event.key.keysym.sym;
               onMouseReleased(_appData.key);
               break;
            }
            default:{
               break;
            }
            }
            updateEvents_loop(Event);
            updateEvents_loop_ImGUI(Event);
         }

         
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
         glClearColor(0.141, 0.133, 0.145, 1.0);
         
         updateRender_loop_ImGUI();

         updateRender_loop();
      
         SDL_GL_SwapWindow(_winData.win);
      }
   }

   void App::updateEvents_loop_ImGUI(SDL_Event& event){
      if (_winData.isImGUI)
         ImGui_ImplSDL2_ProcessEvent(&event);
   }
   void App::updateRender_loop_ImGUI(){
      if (_winData.isImGUI){
         ImGui_ImplOpenGL3_NewFrame();
         ImGui_ImplSDL2_NewFrame();
         ImGui::NewFrame();
         ImGui::SetNextWindowPos( ImVec2(0,0) );
         ImGui::SetNextWindowSize( ImVec2(_winData.size.x * 0.2,_winData.size.y * 0.2) );
         ImGuiWindowFlags flags = (ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
         
         
         ImGui::Begin("Menu", &_winData.isImGUI,flags);
         ImGui::Text("Win pos:   %g %g",_winData.pos.x,_winData.pos.y);
         ImGui::Text("Win size:  %g %g",_winData.size.x,_winData.size.y);
         ImGui::Text("Mouse pos: %g %g",_appData.mousePos.x,_appData.mousePos.y);
         ImGui::Text("Time since start: %g",CoreTime::time_since_start_programm);
         

         ImGui::End();

         // Rendering
         ImGui::Render();
         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      }
   }
};