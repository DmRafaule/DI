#pragma once
#include "stb_image.h"
#include "Core.hpp"



struct Shader;

namespace DI{

struct Texture{
   std::vector<unsigned int*> id;
   std::vector<std::string> u_name;
   std::vector<std::string> name;
   std::vector<unsigned int> mode;
   std::vector<unsigned char*> data;
   std::vector<int*> width;
   std::vector<int*> height;
   std::vector<int*> chanels;
   unsigned int wrap_s   = GL_CLAMP_TO_BORDER; 
   unsigned int wrap_t   = GL_CLAMP_TO_BORDER; 
   unsigned int min_filt = GL_NEAREST; 
   unsigned int mag_filt = GL_NEAREST;

};

class TextureHandler{
public:
   static void Set(Texture &texture, std::vector<std::string> path);
   static void SetFilters(Texture &texture,unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filt, unsigned int mag_filt);
   static void Use(Texture &texture, Shader& shad);
private:
   TextureHandler();
};

}