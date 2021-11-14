#pragma once

#include <string>

class Shader {
public:
   Shader(const std::string& vertex_name, const std::string& fragment_name, const bool& isUseNow = false);
   ~Shader();
   void use();
   inline const uint& getProgram(){ return program; };
private:
   std::string parse(const std::string& name);
   uint compile(uint type, const std::string& source);
private:
   uint program;
};