#include "Shader.hpp"
#include "Buffer.hpp"

namespace DI{
void ShaderHandler::Set(Shader& shader, const std::string& vertex_name, const std::string& fragment_name){
   // Get source of shader files
   std::string vertex_src = ShaderHandler::Parse(vertex_name);
   std::string fragment_src = ShaderHandler::Parse(fragment_name);
   // Set uniforms
   shader.id = glCreateProgram();
   uint vs = Compile(GL_VERTEX_SHADER,vertex_src);
   uint fs = Compile(GL_FRAGMENT_SHADER,fragment_src);

   glAttachShader(shader.id,vs);
   glAttachShader(shader.id,fs);
   glLinkProgram(shader.id);
   glValidateProgram(shader.id);

   glDeleteShader(vs);
   glDeleteShader(fs);
}

void ShaderHandler::Use(Shader& shader){
   glUseProgram(shader.id);
}
std::string ShaderHandler::Parse(const std::string& name){
   std::fstream file;
   std::string fileContent{""};
   file.open(name);
   if (!file.is_open()){
      fileContent = "not_loaded";
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
unsigned int ShaderHandler::Compile(unsigned int type, const std::string& source){
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

void ShaderHandler::SetUniform(Shader &shader, const char* name, const float& arg){
   glUniform1f(glGetUniformLocation(shader.id,name),(float)arg);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const double& arg){
   glUniform1d(glGetUniformLocation(shader.id,name),arg);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const int& arg){
   glUniform1i(glGetUniformLocation(shader.id,name),arg);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const unsigned int& arg){
   glUniform1ui(glGetUniformLocation(shader.id,name),arg);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2){
   glUniform2f(glGetUniformLocation(shader.id,name),arg1,arg2);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3){
   glUniform3f(glGetUniformLocation(shader.id,name),arg1,arg2,arg3);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3, const float& arg4){
   glUniform4f(glGetUniformLocation(shader.id,name),arg1,arg2,arg3,arg4);
}

void ShaderHandler::SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2){
   glUniform2i(glGetUniformLocation(shader.id,name),arg1,arg2);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3){
   glUniform3i(glGetUniformLocation(shader.id,name),arg1,arg2,arg3);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3, const int& arg4){
   glUniform4i(glGetUniformLocation(shader.id,name),arg1,arg2,arg3,arg4);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2){
   glUniform2ui(glGetUniformLocation(shader.id,name),arg1,arg2);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3){
   glUniform3ui(glGetUniformLocation(shader.id,name),arg1,arg2,arg3);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3, const unsigned int& arg4){
   glUniform4ui(glGetUniformLocation(shader.id,name),arg1,arg2,arg3,arg4);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2){
   glUniform2d(glGetUniformLocation(shader.id,name),arg1,arg2);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3){
   glUniform3d(glGetUniformLocation(shader.id,name),arg1,arg2,arg3);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3, const double& arg4){
   glUniform4d(glGetUniformLocation(shader.id,name),arg1,arg2,arg3,arg4);
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const glm::mat2& arg){
   glUniformMatrix2fv(glGetUniformLocation(shader.id,name),1,GL_FALSE,glm::value_ptr(arg));
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const glm::mat3& arg){
   glUniformMatrix3fv(glGetUniformLocation(shader.id,name),1,GL_FALSE,glm::value_ptr(arg));
}
void ShaderHandler::SetUniform(Shader &shader, const char* name, const glm::mat4& arg){
   glUniformMatrix4fv(glGetUniformLocation(shader.id,name),1,GL_FALSE,glm::value_ptr(arg));
}
}