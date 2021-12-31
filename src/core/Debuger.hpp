#pragma once

namespace DI{

struct DebugData{
   int            counterDICalls = 0;      // openGL calls
   int            counterDIVerticies_inUse = 0;  // verticies in viewport
   int            counterDIElements_inUse = 0;   // indicies
   int            counterDIMeshes_inUse = 0;     // rendered meshes
   int            counterDIModels_inUse = 0;     // rendered models
   int            counterDITextures_inUse = 0;   // rendered textures
   int            counterDIShaders_inUse = 0;    // compiled shaders   
   int            counterDIVerticies_inMem = 0;  // verticies in viewport
   int            counterDIElements_inMem = 0;   // indicies
   int            counterDIMeshes_inMem = 0;     // rendered meshes
   int            counterDIModels_inMem = 0;     // rendered models
   int            counterDITextures_inMem = 0;   // rendered textures
   int            counterDIShaders_inMem = 0;    // compiled shaders   
};

}


// Error handling
void ErrorCallback( unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam );
void GLClearError();
void GLCheckError(const char* file, const char* function, int line);

#define GLFindError(x) GLClearError();\
                       x;\
                       GLCheckError(__FILE__,#x,__LINE__);
