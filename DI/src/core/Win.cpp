#include "Win.hpp"
#include "App.hpp"


#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace DI{

   void WinHandler::WinInit(WinData& data){
      DI_LOG_TRACE("Init Win");
      data.isImGUI = false;
      data.isOpen  = true;
      data.pos     = glm::vec2(300,300);
      data.size    = glm::vec2(1260,786);
      data.title   = std::string("DI Game Engine");
      data.flags   = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
      data.win     = SDL_CreateWindow(data.title.c_str(), data.pos.x, data.pos.y, data.size.x, data.size.y, data.flags);    
      data.context = SDL_GL_CreateContext(data.win);
      SDL_GL_MakeCurrent(data.win, data.context);
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
   void WinHandler::WinKill(WinData& data){
      DI_LOG_TRACE("Kill Win");
      SDL_GL_DeleteContext(data.context);
      SDL_DestroyWindow(data.win);
      SDL_Quit();
   }

   void WinHandler::ImGUIInit(WinData& data){
      data.isImGUI = true;
      DI_LOG_TRACE("Init ImGUI");
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO();
      ImGui::StyleColorsDark();

      // Setup Platform/Renderer backends
      ImGui_ImplSDL2_InitForOpenGL(data.win, (void*)data.context);
      ImGui_ImplOpenGL3_Init("#version 130");
   }
   void WinHandler::ImGUIKill(WinData& data){
      DI_LOG_TRACE("Kill ImGUI");
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL2_Shutdown();
      ImGui::DestroyContext();
   }
   
} // namespace DI