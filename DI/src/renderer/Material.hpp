#pragma once

#include "Core.hpp"


namespace DI{

   struct Texture;
   struct Shader;
   enum  UniformType : unsigned int;

   struct Material{
      std::vector<std::pair<std::string,Texture>> samplers;
      std::unordered_map<std::string,std::pair<void*,UniformType>> uniforms;
   };
   
   class MaterialHandler{
   public:
      static void SetSampler(Material& material, const Texture& sampler);
      static void SetShader(Material& material, const Shader& shader);
      static void UseMaterial(Material& material, const Shader& shader);
   };

} // namespace DI
