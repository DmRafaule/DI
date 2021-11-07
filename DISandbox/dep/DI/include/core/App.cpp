#include "GL/glew.h"

#include "App.hpp"
#include "Log.hpp"

#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "AppEvent.hpp"
#include "KeyboardEvent.hpp"

#include "glm/vec2.hpp"
#include "SDL.h"

namespace DI{
   App::App(){

   }
   App::~App(){
      
   }
   void App::run(){
      int width = 1024, height = 786;
      SDL_Window* win = SDL_CreateWindow("OpenGL Win", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);    
      SDL_GLContext Context = SDL_GL_CreateContext(win);
       // Pull out OpenGL defined functions from gpu
      if (GLEW_OK != glewInit()){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glewInit()));
      }
      while(true);
   }
};