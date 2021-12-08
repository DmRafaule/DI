#pragma once

#include "Core.hpp"


namespace DI{

   struct Texture;
   struct Shader;
   enum  UniformType : unsigned int;

   // Consist from uniforms and samplers(textures)
   struct Material{
      std::vector<std::pair<std::string,Texture>> samplers;
      std::unordered_map<std::string,std::pair<void*,UniformType>> uniforms;
   };
   // Conrol material data
   class MaterialHandler{
   public:
      // Set sampler data
      static void SetSampler(Material& material, const Texture& sampler);
      // Set uniform data
      static void SetShader(Material& material, const Shader& shader);
      // Get access to material
      static void UseMaterial(Material& material, const Shader& shader);
   };

} // namespace DI
