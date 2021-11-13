#include "GL/glew.h"
#include "Win.hpp"
#include "App.hpp"
#include "Log.hpp"

#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "KeyboardEvent.hpp"


namespace DI{

   void WinHandler::WinInit(WinData& data){
      DI_LOG_TRACE("Init Win");
      data.isOpen = true;
      data.pos = glm::vec2(300,300);
      data.size = glm::vec2(1260,786);
      data.title = std::string("DI Game Engine");
      data.flags = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
      data.win = SDL_CreateWindow(data.title.c_str(), data.pos.x, data.pos.y, data.size.x, data.size.y, data.flags);    
      data.context = SDL_GL_CreateContext(data.win);

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
   void WinHandler::WinKill(WinData& data){
      DI_LOG_TRACE("Kill Win");
      SDL_Quit();
   }
   
} // namespace DI
