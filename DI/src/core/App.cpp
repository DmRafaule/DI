#include "App.hpp"

namespace DI{

   Scope<DI::AppData> _appData;
   extern Scope<DI::WinData> _winData;
   extern Scope<DI::GUIData> _guiData;
   
   App::App(){
      Log::Init();
      DI_LOG_TRACE("Init App");
      _winData = C_Scope<WinData>();
      _appData = C_Scope<AppData>();
      _guiData = C_Scope<GUIData>();
      WinHandler::WinInit(*_winData);
      GUIHandler::GUIInit(*_guiData);
   }
   App::~App(){
      SceneHandler::Clear();
      GUIHandler::GUIKill(*_guiData);
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
                  GUIHandler::UpdateViewport(*_guiData);
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
            GUIHandler::EventsUpdate(*_guiData,Event);
         }
     
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
         glClearColor(_winData->bg.r,_winData->bg.g,_winData->bg.b, 1.0f );
         
         if (!_winData->isMinimized){
            SceneHandler::Update();
         }
         GUIHandler::Update();
      
         SDL_GL_SwapWindow(_winData->win);
         EventsHandler::AppFrameChanged();
      }
   }

};
