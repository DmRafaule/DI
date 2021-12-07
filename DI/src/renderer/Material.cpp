#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

// NOTES
/*
   Maybe replace DI::ShaderHandler::SetUniform(...) for actual gl functions
*/

namespace DI{
   
   void MaterialHandler::UseMaterial(Material& material, const Shader& shader){
      DI::ShaderHandler::Use(shader);
      for (auto& u : material.uniforms){
         switch(u.second.second){
            case UniformType::FL:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const float*>(u.second.first)));
               break;
            }
            case UniformType::DOB:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const double*>(u.second.first)));
               break;
            }
            case UniformType::IN:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const int*>(u.second.first)));
               break;
            }
            case UniformType::SAMPLER2D:{
               break;
            }
            case UniformType::UIN:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const unsigned int*>(u.second.first)));
               break;
            }
            case UniformType::B:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const bool*>(u.second.first)));
               break;
            }
            case UniformType::FVEC2:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::vec2*>(u.second.first)));
               break;
            }
            case UniformType::FVEC3:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::vec3*>(u.second.first)));
               break;
            }
            case UniformType::FVEC4:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::vec4*>(u.second.first)));
               break;
            }
            case UniformType::IVEC2:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::ivec2*>(u.second.first)));
               break;
            }
            case UniformType::IVEC3:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::ivec3*>(u.second.first)));
               break;
            }
            case UniformType::IVEC4:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::ivec4*>(u.second.first)));
               break;
            }
            case UniformType::UIVEC2:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::uvec2*>(u.second.first)));
               break;
            }
            case UniformType::UIVEC3:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::uvec3*>(u.second.first)));
               break;
            }
            case UniformType::UIVEC4:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::uvec4*>(u.second.first)));
               break;
            }
            case UniformType::DVEC2:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::dvec2*>(u.second.first)));
               break;
            }
            case UniformType::DVEC3:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::dvec3*>(u.second.first)));
               break;
            }
            case UniformType::DVEC4:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::dvec4*>(u.second.first)));
               break;
            }
            case UniformType::MAT2:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::mat2*>(u.second.first)));
               break;
            }
            case UniformType::MAT3:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::mat3*>(u.second.first)));
               break;
            }
            case UniformType::MAT4:{
               DI::ShaderHandler::SetUniform(shader,u.first.c_str(),*(static_cast<const glm::mat4*>(u.second.first)));
               break;
            }
         }
      }
      for (int i = 0; i < material.samplers.size(); ++i){
         DI::TextureHandler::Use(material.samplers[i].second,shader);
      }
   }
   void MaterialHandler::SetSampler(Material& material, const Texture& sampler){
      material.samplers.push_back(std::pair<std::string,Texture>(sampler.sampler,sampler));
   }
   void MaterialHandler::SetShader(Material& material, const Shader& shader){
      for (auto& uni : shader.uniforms){
         switch(uni.second){
            case UniformType::FL:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::DOB:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::IN:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::SAMPLER2D:{
               break;
            }
            case UniformType::UIN:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::B:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::FVEC2:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::FVEC3:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::FVEC4:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::IVEC2:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::IVEC3:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::IVEC4:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::UIVEC2:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::UIVEC3:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::UIVEC4:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::DVEC2:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::DVEC3:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::DVEC4:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::MAT2:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::MAT3:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
            case UniformType::MAT4:{
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(nullptr,uni.second));
               break;
            }
         }
      }
   }

} // namespace DI
