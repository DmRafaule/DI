#pragma once




// Error handling
void ErrorCallback( unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam );
void GLClearError();
void GLCheckError(const char* file, const char* function, int line);

#define GLFindError(x) GLClearError();\
                       x;\
                       GLCheckError(__FILE__,#x,__LINE__);
