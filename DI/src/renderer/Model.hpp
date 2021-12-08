#pragma once

#include "Core.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace DI{

   struct Mesh;
   struct Texture;
   struct Material;
   struct Shader;

   // Model consist from meshes and materials
   struct Model{
      std::vector<Ref<Mesh>> meshes;
      std::vector<Ref<Material>> materials;
   };
   // Setting up Model struct 
   class ModelHandler{
   public:
      // Load data to model
      static void Load(Model& model,std::string path);
      static void Scale(Model &model, const glm::vec3 offset);
      static void Translate(Model &model, const glm::vec3 offset);
      static void Rotate(Model &model,const float angle, const glm::vec3 offset);
   private:
      // Loop throu all nodes in model
      static void processNode(Model& model, aiNode *node, const aiScene *scene);
      // Process all mesh data from one model's node
      static Ref<Mesh> processMesh(Model& model, aiMesh *mesh, const aiScene *scene);
      // Process all material data from one model's node
      static Ref<Material> processMaterial(Model& model, aiMesh *mesh, const aiScene *scene);
      // Process one material data by specific type
      static std::vector<Texture> processMaterialTextures(aiMaterial *mat, aiTextureType type, std::string sampler);
   };

} // namespace DI
