#include "Shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"


namespace DI{

void TextureHandler::Set(Texture &texture, std::vector<std::string> path){
    // Create texture obj
    texture.name = path;
    std::vector<unsigned int> parameters({GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T,GL_TEXTURE_MIN_FILTER,GL_TEXTURE_MAG_FILTER});

    for (int i = 0; i < texture.name.size(); ++i){ 
        texture.id.push_back(new unsigned int());
        texture.height.push_back(new int());
        texture.width.push_back(new int());
        texture.chanels.push_back(new int());
        texture.u_name.push_back("u_tex" + std::to_string(i));
    }

   // For now texture handler
   for (int i = 0; i < texture.name.size(); ++i){
       glGenTextures(1,texture.id[i]);
       glBindTexture(GL_TEXTURE_2D,*texture.id[i]);
       // Define texture parameters
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,texture.wrap_s);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,texture.wrap_t);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texture.min_filt);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texture.mag_filt);
       // Flip texture
       // Loading image
       stbi_set_flip_vertically_on_load(true);  
       texture.data.push_back(stbi_load(texture.name[i].c_str(),texture.width[i],texture.height[i],texture.chanels[i],0));
       if (texture.data.back()){
           if (*texture.chanels[i] == 4){
               texture.mode.push_back(GL_RGBA);
           }
           else if (*texture.chanels[i] == 3){
               texture.mode.push_back(GL_RGB);
           }
           // Bind image to texture
           glTexImage2D(GL_TEXTURE_2D,0,texture.mode[i],*texture.width[i],*texture.height[i],0,texture.mode[i],GL_UNSIGNED_BYTE,texture.data.back());
           glGenerateMipmap(GL_TEXTURE_2D);
           stbi_image_free(texture.data.back());
       }
       else{
           DI_LOG_ERROR("STB CALLBACK: fail to load image.");
       }
   }
}
void TextureHandler::SetFilters(Texture &texture,unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filt, unsigned int mag_filt){
    texture.wrap_s   = wrap_s;
    texture.wrap_t   = wrap_t;
    texture.min_filt = min_filt;
    texture.mag_filt = mag_filt;
}
void TextureHandler::Use(Texture &texture, Shader& shad){
   // Bind texture to polygon
    for (int i = 0; i < texture.name.size(); i++){
        ShaderHandler::SetUniform(shad,texture.u_name[i].c_str(), i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D,*texture.id[i]);
    }
}

}