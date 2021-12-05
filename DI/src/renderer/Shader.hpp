#pragma once

#include "Core.hpp"

namespace DI{

enum UniformType : unsigned int{
   FL,
   IN,
   UIN,
   DOB,
   B,
   FVEC2,
   FVEC3,
   FVEC4,
   IVEC2,
   IVEC3,
   IVEC4,
   DVEC2,
   DVEC3,
   DVEC4,
   UIVEC2,
   UIVEC3,
   UIVEC4,
   MAT2,
   MAT3,
   MAT4
};
struct Shader{
   unsigned int id;
   std::unordered_map<std::string,UniformType> uniforms;
};
class ShaderHandler{
public:
   static void Set(Shader &shader, const std::string& vertex_path, const std::string& fragment_path);
   static void Use(Shader &shader);
   static std::string Parse(const std::string& name);
   static std::string GetType(const UniformType type);

   static void SetUniform(const Shader &shader, const char* name, const float& arg);
   static void SetUniform(const Shader &shader, const char* name, const double& arg);
   static void SetUniform(const Shader &shader, const char* name, const int& arg);
   static void SetUniform(const Shader &shader, const char* name, const unsigned int& arg);
   static void SetUniform(const Shader &shader, const char* name, const float& arg1, const float& arg2);
   static void SetUniform(const Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3);
   static void SetUniform(const Shader &shader, const char* name, const float& arg1, const float& arg2, const float& arg3, const float& arg4);
   static void SetUniform(const Shader &shader, const char* name, const int& arg1, const int& arg2);
   static void SetUniform(const Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3);
   static void SetUniform(const Shader &shader, const char* name, const int& arg1, const int& arg2, const int& arg3, const int& arg4);
   static void SetUniform(const Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2);
   static void SetUniform(const Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3);
   static void SetUniform(const Shader &shader, const char* name, const unsigned int& arg1, const unsigned int& arg2, const unsigned int& arg3, const unsigned int& arg4);
   static void SetUniform(const Shader &shader, const char* name, const double& arg1, const double& arg2);
   static void SetUniform(const Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3);
   static void SetUniform(const Shader &shader, const char* name, const double& arg1, const double& arg2, const double& arg3, const double& arg4);
   static void SetUniform(const Shader &shader, const char* name, const glm::mat2& arg);
   static void SetUniform(const Shader &shader, const char* name, const glm::mat3& arg);
   static void SetUniform(const Shader &shader, const char* name, const glm::mat4& arg);
private:
   static unsigned int Compile(unsigned int type, const std::string& source);
   static void processUniforms(Shader &shader, const std::string& source);
   static void subProcessUniformBlock(Shader& shader, std::string src, const std::string u_name, std::string type_compare);
   static void subProcessUniformSimple(Shader& shader, std::string u_name, std::string type_compare);
   static void subProcessUniformComplex(Shader& shader, std::string u_name, std::string type_compare);
   static void setNewUniform(Shader& shader, const int u_count, std::string u_name, std::string type_compare);
   ShaderHandler();
};

}
