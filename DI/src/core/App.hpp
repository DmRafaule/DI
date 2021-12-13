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
      float constant;
      float linear;
      float quadratic;
      glm::vec3 vslot1;
      glm::vec3 pointPos;
      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;
      glm::vec3 ambient_;
      glm::vec3 diffuse_;
      glm::vec3 specular_;
      float constant_;
      float linear_;
      float quadratic_;
      float shineness_;
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
