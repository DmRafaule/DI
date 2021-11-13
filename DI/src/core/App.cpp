#include "GL/glew.h"

#include "App.hpp"
#include "Win.hpp"
#include "Log.hpp"
#include "AppEvent.hpp"
#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "AppEvent.hpp"
#include "KeyboardEvent.hpp"



namespace DI{
   
   App::App(){
      Log::Init();
      DI_LOG_TRACE("Init App");
      WinHandler::WinInit(_winData);
   }
   App::~App(){
      DI_LOG_TRACE("Kill App");
   }
   void App::run(){
      while(_winData.isOpen){
         SDL_Event Event;
         while (SDL_PollEvent(&Event)){
            switch (Event.type){
            case SDL_QUIT:{
               _winData.isOpen = false;
               WinHandler::WinKill(_winData);
               break;
            }
            case SDL_WINDOWEVENT:{
               switch (Event.window.event){
               case SDL_WINDOWEVENT_RESIZED:{
                  WinResize e(glm::vec2(Event.window.data1,Event.window.data2));
                  _winData.size = e.getSize();
                  onWinResized(e.getSize());
                  DI_LOG_INFO(e);
                  break;
               }
               case SDL_WINDOWEVENT_CLOSE:{
                  WinClose e;
                  _winData.isOpen = false;
                  DI_LOG_INFO(e);
                  break;
               }
               case SDL_WINDOWEVENT_TAKE_FOCUS:{
                  WinFocus e(true);
                  onWinFocused();
                  DI_LOG_INFO(e);
                  break;
               }
               case SDL_WINDOWEVENT_MOVED:{
                  WinMoved e(glm::vec2(Event.window.data1,Event.window.data2));
                  _winData.pos = e.getPos();
                  onWinMoved(e.getPos());
                  DI_LOG_INFO(e);
                  break;
               }
               }
               break;
            }
            case SDL_KEYUP:{
               KeyReleased a(Event.key.keysym.sym);
               _appData.key = a.getKeyCode();
               onKeyReleased(a.getKeyCode());
               DI_LOG_INFO(a);
               break;
            }
            case SDL_KEYDOWN:{
              KeyPressed a(Event.key.keysym.sym,Event.key.repeat);
               _appData.key = a.getKeyCode(); 
               _appData.isKey_repeat = a.getRepeatCount(); 
               onKeyPressed(a.getKeyCode(),a.getRepeatCount());
               DI_LOG_INFO(a);
               break;
            }
            case SDL_MOUSEMOTION:{
               MouseMoved a(glm::vec2(Event.motion.x,Event.motion.y));
               _appData.mousePos = a.getPos();
               onMouseMoved(a.getPos());
               DI_LOG_INFO(a);
               break;
            }
            case SDL_MOUSEWHEEL:{
               MouseScrolled a(glm::vec2(Event.wheel.x,Event.wheel.y));
               _appData.mouseWheelOffset = a.getOffset();
               onMouseScrolled(a.getOffset());
               DI_LOG_INFO(a);
            }
            case SDL_MOUSEBUTTONDOWN:{
               MouseButtonPressed a(Event.key.keysym.sym);
               _appData.key = a.getMouseButton();
               onMousePressed(a.getMouseButton(),0);
               DI_LOG_INFO(a);
               break;
            }
            case SDL_MOUSEBUTTONUP:{
               MouseButtonReleased a(Event.key.keysym.sym);
               _appData.key = a.getMouseButton();
               onMouseReleased(a.getMouseButton());
               DI_LOG_INFO(a);
               break;
            }
            default:{
               break;
            }
            }
            updateEvents_loop(Event);
         }
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
         glClearColor(0.141, 0.133, 0.145, 1.0);

         updateRender_loop();
      
         SDL_GL_SwapWindow(_winData.win);
      }
   }
};