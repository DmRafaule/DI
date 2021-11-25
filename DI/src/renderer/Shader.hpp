#pragma once

#include <string>
#include <list>
#include "Buffer.hpp"
#include <unordered_map>

namespace DI{

struct Shader{
   unsigned int id;
};
class ShaderHandler{
public:
   static void Set(Shader &shader, const std::string& vertex_path, const std::string& fragment_path);
   static void Use(Shader &shader);
   static std::string Parse(const std::string& name);

   static void SetUniform(Shader &shader, const char* name, const float& arg);
   static void SetUniform(Shader &shader, const char* name, const double& arg);
   static void SetUniform(Shader &shader, const char* name, const int& arg);
   static void SetUniform(Shader &shader, const char* name, const unsigned int& arg);
   static void SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2);
   static void SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3);
   static void SetUniform(Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3, const float& arg4);
   static void SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2);
   static void SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3);
   static void SetUniform(Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3, const int& arg4);
   static void SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2);
   static void SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3);
   static void SetUniform(Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3, const unsigned int& arg4);
   static void SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2);
   static void SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3);
   static void SetUniform(Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3, const double& arg4);
   static void SetUniform(Shader &shader, const char* name, const glm::mat2& arg);
   static void SetUniform(Shader &shader, const char* name, const glm::mat3& arg);
   static void SetUniform(Shader &shader, const char* name, const glm::mat4& arg);
private:
   static unsigned int Compile(unsigned int type, const std::string& source);
   ShaderHandler();
};

}
