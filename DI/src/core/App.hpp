#pragma once
#include "Core.hpp"
#include "Win.hpp"
#include "SDL.h"


namespace DI{

   struct AppData {
      int         key;
      bool        isKey_repeat;
      glm::vec2   mousePos;
      glm::vec2   mouseWheelOffset;
   };

   class App{
   public:
      App();
      virtual ~App();
      void run();

      // To be used in client side of app
      virtual void updateEvents_loop(SDL_Event& event){};
      virtual void updateRender_loop(){};

      virtual void onWinResized(glm::vec2 size){};
      virtual void onWinMoved(glm::vec2 pos){};
      virtual void onWinFocused(){};
      virtual void onKeyPressed(int key, bool isKey_repeat){};
      virtual void onKeyReleased(int key){};
      virtual void onMouseMoved(glm::vec2 pos){};
      virtual void onMouseScrolled(glm::vec2 offset){};
      virtual void onMousePressed(int key, bool isKey_repeat){};
      virtual void onMouseReleased(int key){};

   protected:
      WinData _winData;
      AppData _appData;
   };
   //To be defind in client
   App* CreateApp();
};