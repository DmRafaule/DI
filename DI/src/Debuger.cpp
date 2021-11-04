#include "Debuger.hpp"
#include "Time.hpp"
#include "SDL.h"

#include <iostream>
#include <GL/glew.h>


// Error handling
void ErrorCallback( unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam ){
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, 
             severity, 
             message );
}
void GLClearError(){
    // Clear error vbo of OpenGL
    while(glGetError() != GL_NO_ERROR);
}
void GLCheckError(const char* file, const char* function, int line){
    // Get all acure errors
    uint err;
    while(err = glGetError()){
      std::cout << "GL ERROR: 0x0" << std::hex << err << ", LINE " << std::dec << line << ", FUNCTION " << function << ", FILE " << file <<std::endl;
    }
}



void FramRateHandler::UpdateFrameRate(){
  // Update frame rate
  if ( max_framDelay > CoreTime::tic){
    SDL_Delay(max_framDelay - CoreTime::tic);
  }
  frame_counter += 1;
  time_counter  += CoreTime::tic;
  if (time_counter >= 1.0f){
    time_counter  = 0;
    frame_counter = 0;
  }
}