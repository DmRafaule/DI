#pragma once
#include "Core.hpp"
#include "Win.hpp"
#include "SDL.h"
#include "Buffer.hpp"

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
   protected:
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


      // ImGUI functions
      virtual void updateRender_loop_ImGUI();
   private:
      void updateEvents_loop_ImGUI(SDL_Event& event);
   protected:
      Scope<WinData> _winData;
      Scope<AppData> _appData;
   };
   //To be defind in client
   App* CreateApp();
};