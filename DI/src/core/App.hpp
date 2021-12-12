#pragma once
#include "Core.hpp"
#include "Win.hpp"
#include "Scene.hpp"
#include "Event.hpp"

namespace DI{

   struct AppData {
      int         key;
      bool        isKey_repeat;
      glm::vec2   mousePos;
      glm::vec2   mouseWheelOffset;
   } ;
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
      // ImGUI functions
      virtual void updateRender_loop_ImGUI();
   private:
      void updateEvents_loop_ImGUI(SDL_Event& event);
   protected:
   };
   //To be defind in client
   App* CreateApp();
};
