#pragma once

#include "Core.hpp"

namespace DI {
   // Contain vertices data
   struct Vertice{
      void         *data;
      unsigned int  count;
      unsigned int  size;// How long data in one vertice
   };
   // Contain element data(Indices)
   struct Element{
      void         *data;
      unsigned int  count;
   };
   // Contain buffers (till now this ones)
   struct Buffer{
      unsigned int ebo;
      unsigned int vao;
      unsigned int vbo;
   };
   // Containg data about meshe
   struct Mesh{
      Buffer       buffer;
      Vertice      verticies;
      Element      elements; 
      glm::mat4    model_matrix;
   };
  
   // Control mesh data
   class MeshHandler{
   public:
      // Filed up mesh data
      static void Set(Mesh &mesh);
      // Scale mesh
      static void Scale(Mesh &mesh, const glm::vec3 offset);
      // Translate mesh
      static void Translate(Mesh &mesh, const glm::vec3 offset);
      // Rotate mesh
      static void Rotate(Mesh &mesh,const float angle, const glm::vec3 offset);
   private:
      MeshHandler();
   };

}