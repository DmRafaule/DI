#include "Utils.hpp"
#include "Log.hpp"
#include <stdio.h> 

#include <dirent.h>

namespace DI{

std::unordered_map<std::string,std::vector<std::string>> ListDirectory(const std::string path){
  std::unordered_map<std::string,std::vector<std::string>> buffer;
  DIR * d = opendir(path.c_str());
  if (d != NULL){ 
    struct dirent * dir;
    while ((dir = readdir(d)) != NULL){ // if we were able to read somehting from the directory
      if(dir-> d_type != DT_DIR){ // if the type is not directory just print it with blue color
        buffer.emplace(dir->d_name,std::vector<std::string>(0));
      }
      else
        if(dir -> d_type == DT_DIR && strcmp(".",dir->d_name) != 0){ // if it is a directory
          buffer.emplace(dir->d_name,std::vector<std::string>(1));
          char d_path[255]; // here I am using sprintf which is safer than strcat
          sprintf(d_path, "%s/%s", path.c_str(), dir->d_name);
        }
    }
    closedir(d); // finally close the directory
  }
  return buffer;
}

};