#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


namespace DI{
   
   void MaterialHandler::UseMaterial(Material& material, const Shader& shader){
      for (int i = 0; i < material.samplers.size(); ++i){
         DI::TextureHandler::Use(material.samplers[i].second,shader);
      }
      for (auto& u : material.uniforms){
        // DI::ShaderHandler::SetUniform(shader,u.first,reinterpret_cast<float&>(u.second.first));//HERE
      }
   }
   void MaterialHandler::SetSampler(Material& material, const Texture& sampler){
      material.samplers.push_back(std::pair<std::string,Texture>(sampler.sampler,sampler));
   }
   void MaterialHandler::SetShader(Material& material, const Shader& shader){
      for (auto& uni : shader.uniforms){
         switch(uni.second){
            case UniformType::FL:{
               Ref<float> data(new float(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::DOB:{
               Ref<double> data(new double(1.0d));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::IN:{
               Ref<int> data(new int(1));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::UIN:{
               Ref<unsigned int> data(new unsigned int(1u));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::B:{
               Ref<bool> data(new bool(true));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::FVEC2:{
               Ref<glm::vec2> data(new glm::vec2(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::FVEC3:{
               Ref<glm::vec3> data(new glm::vec3(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::FVEC4:{
               Ref<glm::vec4> data(new glm::vec4(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::IVEC2:{
               Ref<glm::ivec2> data(new glm::ivec2(1));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::IVEC3:{
               Ref<glm::ivec3> data(new glm::ivec3(1));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::IVEC4:{
               Ref<glm::ivec4> data(new glm::ivec4(1));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::UIVEC2:{
               Ref<glm::uvec2> data(new glm::uvec2(1u));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::UIVEC3:{
               Ref<glm::uvec3> data(new glm::uvec3(1u));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::UIVEC4:{
               Ref<glm::uvec4> data(new glm::uvec4(1u));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::DVEC2:{
               Ref<glm::dvec2> data(new glm::dvec2(1.0));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::DVEC3:{
               Ref<glm::dvec3> data(new glm::dvec3(1.0));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::DVEC4:{
               Ref<glm::dvec4> data(new glm::dvec4(1.0));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::MAT2:{
               Ref<glm::mat2> data(new glm::mat2(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::MAT3:{
               Ref<glm::mat3> data(new glm::mat3(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
            case UniformType::MAT4:{
               Ref<glm::mat4> data(new glm::mat4(1.0f));
               material.uniforms.emplace(uni.first,std::pair<void*,UniformType>(&data,uni.second));
               break;
            }
         }
      }
   }

} // namespace DI
