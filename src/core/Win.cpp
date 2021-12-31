#include "Win.hpp"

namespace DI{
   Scope<DI::WinData> _winData;
   void WinHandler::Init(WinData& data){
      DI_LOG_TRACE("WinHandler say: Init Win.");
      data.bg = glm::vec3(41.f/255.f,46.f/255.f,54.f/255.f);
      data.isMinimized = false;
      data.isOpen  = true;
      data.pos     = glm::vec2(300,300);
      data.size    = glm::vec2(1260,786);
      data.title   = std::string("DI Game Engine");
      data.flags   = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
      data.win     = SDL_CreateWindow(data.title.c_str(), data.pos.x, data.pos.y, data.size.x, data.size.y, data.flags);    
      data.context = SDL_GL_CreateContext(data.win);
      SDL_GL_MakeCurrent(data.win, data.context);
      //SDL_ShowCursor(SDL_DISABLE);
      //SDL_WarpMouseInWindow(data.win,data.size.x/2.f,data.size.y/2.f);
      SDL_GL_SetSwapInterval(1); // Enable vsync

      // Pull out OpenGL defined functions from gpu
      if (GLEW_OK != glewInit()){
         DI_LOG_ERROR("%s",glewGetErrorString(glewInit()));
      }
      // Init debug stuff
      glEnable( GL_DEBUG_OUTPUT );
      // Init testing depth of pixels
      glEnable( GL_DEPTH_TEST );
      glDebugMessageCallback( ErrorCallback, 0 );
      // Init drawing mode
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   }
   void WinHandler::Kill(WinData& data){
      DI_LOG_TRACE("WinHandler say: Kill Win.");
      SDL_GL_DeleteContext(data.context);
      SDL_DestroyWindow(data.win);
      SDL_Quit();
   }
   
} // namespace DI
