#pragma once

#include "Core.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace DI{

   struct Mesh;

   struct Model{
      std::vector<Ref<Mesh>>  meshes;
   };

   class ModelHandler{
   public:
      static void Load(Model& model,std::string path);
   private:
      static void processNode(Model& model, aiNode *node, const aiScene *scene);
      static Ref<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
   };

} // namespace DI
