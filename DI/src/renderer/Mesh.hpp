#pragma once

#include "Core.hpp"

namespace DI {
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

}