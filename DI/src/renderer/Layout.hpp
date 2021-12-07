#pragma once 

#include "Core.hpp"


namespace DI{
   
   struct Texture;
   struct Shader;
   // Contain layout data
   struct Layout{
      unsigned int  index;
      unsigned int  count;
      unsigned int  type;
      unsigned char normalized;
      unsigned int  stribe;
      unsigned int  entry;
   };
   // Set up all attributes for buffer(it depends from shader passes)
   class LayoutHandler{
   public:
      static void Set(const std::string& vertShader_path);
   private:
      static int get_layout_size(const std::string& src);
      LayoutHandler();
   };
   
} // namespace DI
