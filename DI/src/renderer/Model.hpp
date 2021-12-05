#pragma once

#include "Core.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace DI{

   struct Mesh;
   struct Texture;
   struct Material;

   struct Model{
      std::vector<Ref<Mesh>> meshes;
      std::vector<Ref<Material>> materials;
   };

   class ModelHandler{
   public:
      static void Load(Model& model,std::string path);
   private:
      static void processNode(Model& model, aiNode *node, const aiScene *scene);
      static Ref<Mesh> processMesh(Model& model, aiMesh *mesh, const aiScene *scene);
      static Ref<Material> processMaterial(Model& model, aiMesh *mesh, const aiScene *scene);
      static std::vector<Texture> processMaterialTextures(aiMaterial *mat, aiTextureType type, std::string sampler);
   };

} // namespace DI
