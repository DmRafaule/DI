#pragma once
#include "stb_image.h"
#include "Core.hpp"



struct Shader;

namespace DI{

struct Texture{
   std::string sampler;
   std::string path;
   unsigned int id;
   
   unsigned int mode;
   unsigned char* data;
   unsigned int slot;

   unsigned int wrap_s   = GL_CLAMP_TO_BORDER; 
   unsigned int wrap_t   = GL_CLAMP_TO_BORDER; 
   unsigned int min_filt = GL_NEAREST; 
   unsigned int mag_filt = GL_NEAREST;
   int width;
   int height;
   int chanels;

};

class TextureHandler{
public:
   static void Set(Texture &texture, const std::string path);
   static void SetFilters(Texture &texture, unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filt, unsigned int mag_filt);
   static void Use(Texture &texture,const Shader& shad);
private:
   TextureHandler();
};

}