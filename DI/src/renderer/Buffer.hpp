#pragma once 

#include <string>
#include <list>
#include <unordered_map>
#include <functional>
#include <glm/gtc/type_ptr.hpp>


namespace DI{
   // Contain layout data
   struct Layout{
      unsigned int  index;
      unsigned int  count;
      unsigned int  type;
      unsigned char normalized;
      unsigned int  stribe;
      unsigned int  entry;
   };
   // Contain vertices data
   struct Vertice{
      void         *data;
      unsigned int  count;
   };
   // Contain element data
   struct Element{// Indices
      void         *data;
      unsigned int  count;
   };
   // Contain buffers till now this ones
   struct Buffer{
      unsigned int ebo;
      unsigned int vao;
      unsigned int vbo;
   };
   // Containg data about meshes
   struct Mesh{
      Buffer       buffer;
      Vertice      verticies;
      Element      elements; 
      glm::mat4    model_matrix;
   };
  
   // Set up mesh
   class MeshHandler{
   public:
      static void Set(Mesh &mesh);
      static void Scale(Mesh &mesh, const glm::vec3 offset);
      static void Translate(Mesh &mesh, const glm::vec3 offset);
      static void Rotate(Mesh &mesh,const float angle, const glm::vec3 offset);
   private:
      MeshHandler();
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
