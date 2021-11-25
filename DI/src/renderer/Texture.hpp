#pragma once
#include "stb_image.h"
#include "Core.hpp"



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

};

class TextureHandler{
public:
   static void Set(Texture &texture, std::vector<std::string> path,std::vector<unsigned int> filters);
   static void Use(Texture &texture, Shader& shad);
private:
   TextureHandler();
};

}