#pragma once 

#include "Core.hpp"
#include "Event.hpp"
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
   };
   static WinData g_winData;

   class WinHandler{
   public:
      static bool WinInit();
      static bool WinKill();
      static bool WinUpdate();
   private:
      WinHandler();
   };


}; // namespace DI
