#pragma once

#include <string>

namespace DI{
class Shader {
public:
   Shader(const std::string& vertex_name, const std::string& fragment_name, const bool& isUseNow = false);
   ~Shader();
   void use();
   inline const uint& getProgram(){ return program; };
   static std::string parse(const std::string& name);
private:
   uint compile(uint type, const std::string& source);
private:
   uint program;
};
}

// NOTE:
/*
   Maybe you should improve your shader parser in that way that pogramm will 
   know what types of uniforms you are using and (then process this into sending uniforms functions)
*/