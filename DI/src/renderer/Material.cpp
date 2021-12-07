#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


namespace DI{
   
   void MaterialHandler::UseMaterial(Material& material, const Shader& shader){
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
               float* data = new float(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::DOB:{
               double* data = new double(1.0d);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::IN:{
               int* data = new int(1);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::UIN:{
               unsigned int* data = new unsigned int(1u);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::B:{
               bool* data = new bool(true);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::FVEC2:{
               glm::vec2* data = new glm::vec2(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::FVEC3:{
               glm::vec3* data = new glm::vec3(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::FVEC4:{
               glm::vec4* data = new glm::vec4(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::IVEC2:{
               glm::ivec2* data = new glm::ivec2(1);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::IVEC3:{
               glm::ivec3* data = new glm::ivec3(1);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::IVEC4:{
               glm::ivec4* data = new glm::ivec4(1);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::UIVEC2:{
               glm::uvec2* data = new glm::uvec2(1u);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::UIVEC3:{
               glm::uvec3* data = new glm::uvec3(1u);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::UIVEC4:{
               glm::uvec4* data = new glm::uvec4(1u);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::DVEC2:{
               glm::dvec2* data = new glm::dvec2(1.0);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::DVEC3:{
               glm::dvec3* data = new glm::dvec3(1.0);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::DVEC4:{
               glm::dvec4* data = new glm::dvec4(1.0);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::MAT2:{
               glm::mat2* data = new glm::mat2(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::MAT3:{
               glm::mat3* data = new glm::mat3(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
            case UniformType::MAT4:{
               glm::mat4* data = new glm::mat4(1.0f);
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(data,uni.second));
               break;
            }
         }
      }
   }

} // namespace DI
