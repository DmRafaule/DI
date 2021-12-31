#pragma once 

#include "Core.hpp"
#include "SDL.h"

namespace DI{
   // For now supporting only one window

   struct WinData{
      glm::vec3      bg;
      glm::vec2      size;
      glm::vec2      pos; 
      std::string    title;
      Uint32         flags;
      SDL_Window*    win;
      SDL_GLContext  context;
      bool           isOpen;
      bool           isMinimized;

   };

   class WinHandler{
   public:
      static void Init(WinData& data);
      static void Kill(WinData& data);;
   private:
   };



}; // namespace DI
