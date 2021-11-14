#pragma once 

#include "Core.hpp"
#include "SDL.h"

namespace DI{
   // For now supporting only one window

   struct WinData{
      glm::vec2      size;
      glm::vec2      pos; 
      std::string    title;
      Uint32         flags;
      SDL_Window*    win;
      SDL_GLContext  context;
      bool           isOpen;
      bool           isImGUI;
   };

   class WinHandler{
   public:
      static void WinInit(WinData& data);
      static void WinKill(WinData& data);
      static void ImGUIInit(WinData& data);
      static void ImGUIKill(WinData& data);
   private:
   };



}; // namespace DI
