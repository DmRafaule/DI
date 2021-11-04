#include <GL/glew.h>

#include <SDL.h>

#include <iostream>
#include <vector>

#include "Debuger.hpp"
#include "Time.hpp"


int main (int argc, char **argv){
    int width = 1024, height = 768;
    SDL_Window* win = SDL_CreateWindow("GameEngine", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);    
    SDL_GLContext Context = SDL_GL_CreateContext(win);

    // Pull out OpenGL defined functions from gpu
    if (GLEW_OK != glewInit()){
      fprintf(stderr, "Error: %s\n", glewGetErrorString(glewInit()));
    }
    // Init debug stuff
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( ErrorCallback, 0 );

    bool Running = true;
    while (Running){
        CoreTime core_time;
        
        SDL_Event Event;
        while (SDL_PollEvent(&Event)){
            switch (Event.type){
            case SDL_QUIT:{
                Running = false;
                break;
            }
            default:{
                break;
            }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
        glClearColor(0.141, 0.133, 0.145, 1.0);


        SDL_GL_SwapWindow(win);
    }


    return 0;
}