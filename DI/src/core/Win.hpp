#pragma once 

#include "Core.hpp"
#include "SDL.h"

namespace DI{
   // For now supporting only one window

   struct WinData{
      std::vector<glm::vec2>      size;
      std::vector<glm::vec2>      pos; 
      std::vector<std::string>    title;
      std::vector<Uint32>         flags;
      std::vector<SDL_Window*>    win;
      std::vector<SDL_GLContext>  context;
      uint                        id = -1;
      bool                        isOpen;
   };

   class WinHandler{
   public:
      static void WinInit();
      static void WinKill();
      static void WinUpdate();
      static void WinEvUpdate();
   private:
      WinHandler();
   };



}; // namespace DI
