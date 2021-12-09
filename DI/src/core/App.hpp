#pragma once
#include "Core.hpp"
#include "Win.hpp"
#include "Layer.hpp"

namespace DI{

   struct AppData {
      int         key;
      bool        isKey_repeat;
      glm::vec2   mousePos;
      glm::vec2   mouseWheelOffset;
   };
   struct ImGUIData{
      float slot0;
      float slot1;
      float slot2;
      float slot3;
      float slot4;
      float slot5;
      float slot6;
      float slot7;
      float slot8;
      glm::vec3 vslot1;
      glm::vec3 vslot2;
      glm::vec3 vslot3;
   };

   class App{
   public:
      App();
      virtual ~App();
      void run();
   protected:
      void UseMe();
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
      Scope<WinData>    _winData;
      Scope<AppData>    _appData;
      Scope<ImGUIData>  _imguiData;
   };
   //To be defind in client
   App* CreateApp();
};