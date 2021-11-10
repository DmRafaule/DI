#include "GL/glew.h"
#include "Win.hpp"
#include "App.hpp"
#include "Log.hpp"

#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "AppEvent.hpp"
#include "KeyboardEvent.hpp"


namespace DI{
   
   WinData g_winData;


   void WinHandler::WinInit(){
      DI_LOG_TRACE("Init Win");
      g_winData.isOpen = true;
      g_winData.id++;
      g_winData.pos.push_back(glm::vec2(300,300));
      g_winData.size.push_back(glm::vec2(1260,786));
      g_winData.title.push_back(std::string("DI Game Engine"));
      g_winData.flags.push_back(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
      g_winData.win.push_back(SDL_CreateWindow(g_winData.title.at(g_winData.id).c_str(), 
                                               g_winData.pos.at(g_winData.id).x, 
                                               g_winData.pos.at(g_winData.id).y, 
                                               g_winData.size.at(g_winData.id).x, 
                                               g_winData.size.at(g_winData.id).y, 
                                               g_winData.flags.at(g_winData.id)));    
      g_winData.context.push_back(SDL_GL_CreateContext(g_winData.win.at(g_winData.id)));

      // Pull out OpenGL defined functions from gpu
      if (GLEW_OK != glewInit()){
         DI_LOG_ERROR("%s",glewGetErrorString(glewInit()));
      }
      // Init debug stuff
      glEnable( GL_DEBUG_OUTPUT );
      // Init testing depth of pixels
      glEnable( GL_DEPTH_TEST );
      //glDebugMessageCallback( ErrorCallback, 0 );
      // Init drawing mode
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   }
   void WinHandler::WinKill(){
      DI_LOG_TRACE("Kill Win");
      SDL_Quit();
   }
   void WinHandler::WinEvUpdate(){
      SDL_Event Event;
      while (SDL_PollEvent(&Event)){
         switch (Event.type){
         case SDL_QUIT:{
            g_winData.isOpen = false;
            WinHandler::WinKill();
            break;
         }
         case SDL_WINDOWEVENT:{
            switch (Event.window.event){
            case SDL_WINDOWEVENT_RESIZED:{
               WinResize e(glm::vec2(Event.window.data1,Event.window.data2));
               DI_LOG_INFO(e);
               break;
            }
            case SDL_WINDOWEVENT_CLOSE:{
               WinClose e;
               DI_LOG_INFO(e);
               break;
            }
            case SDL_WINDOWEVENT_TAKE_FOCUS:{
               WinFocus e(true);
               DI_LOG_INFO(e);
               break;
            }
            case SDL_WINDOWEVENT_MOVED:{
               WinMoved e(glm::vec2(Event.window.data1,Event.window.data2));
               DI_LOG_INFO(e);
               break;
            }
            }
         }
         default:{
            break;
         }
         }
      }
   }
   void WinHandler::WinUpdate(){
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
      glClearColor(0.141, 0.133, 0.145, 1.0);

      
      SDL_GL_SwapWindow(g_winData.win.at(g_winData.id));
   }
} // namespace DI
