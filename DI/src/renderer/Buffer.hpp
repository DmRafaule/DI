#pragma once 

#include "Core.hpp"


namespace DI{
   struct Layout{
      unsigned int  index;
      unsigned int  count;
      unsigned int  type;
      unsigned char normalized;
      unsigned int  stribe;
      unsigned int  entry;
   };
   struct Vertice{
      void         *data;
      unsigned int  count;
   };
   struct Element{
      void         *data;
      unsigned int  count;
   };
   struct Buffer{
      unsigned int ebo;
      unsigned int vao;
      unsigned int vbo;
      Vertice      verticies;
      Element      elements; 
   };
  
   class BufferHandler{
   public:
      static void Set(Buffer &buffer);
   private:
      BufferHandler();
   };

   class LayoutHandler{
   public:
      static void Set(const std::string& vertShader);
   private:
      static int get_layout_size(const std::string& src);
      LayoutHandler();
   };

   
} // namespace DI
