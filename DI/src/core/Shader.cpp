#include "Core.hpp"
#include "Shader.hpp"

#include <GL/glew.h>


Shader::Shader(const std::string& vertex_name, const std::string& fragment_name, const bool& isUseNow){
   program = glCreateProgram();
   uint vs = compile(GL_VERTEX_SHADER,parse(vertex_name));
   uint fs = compile(GL_FRAGMENT_SHADER,parse(fragment_name));

   glAttachShader(program,vs);
   glAttachShader(program,fs);
   glLinkProgram(program);
   glValidateProgram(program);

   glDeleteShader(vs);
   glDeleteShader(fs);

   if (isUseNow)
      glUseProgram(program);
}
Shader::~Shader(){

}
void Shader::use(){
   glUseProgram(program);
}
std::string Shader::parse(const std::string& name){
   std::fstream file;
   std::string fileContent{""};
   file.open("../res/shaders/" + name);
   if (!file.is_open()){
       std::cout << "Failed opening file " << name << std::endl;
   }
   else{
       std::string buffer;
       while(std::getline(file,buffer)){
           fileContent += buffer + "\n";
       }
       file.close();
   }
   return fileContent;
}
uint Shader::compile(uint type, const std::string& source){
   unsigned int id = glCreateShader(type);
   const char* src = source.c_str();
   glShaderSource(id,1,&src,nullptr); 
   glCompileShader(id);

   int result;
   glGetShaderiv(id,GL_COMPILE_STATUS,&result);
   if (result == GL_FALSE){
       int length;
       glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
       char* message =  (char*)alloca(length * sizeof(char));
       glGetShaderInfoLog(id,length,&length,message);
       std::cout << "Faile compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader.\n";
       std::cout << message << std::endl;
       glDeleteShader(id);
       return 1;
   }

   return id;
}
