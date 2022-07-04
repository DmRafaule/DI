#pragma once
#include "Core.hpp"
#include "Win.hpp"
#include "Scene.hpp"
#include "Event.hpp"
#include "Gui.hpp"

namespace DI{

   struct AppData {
      int         key;
      bool        isKey_repeat;
      glm::vec2   mousePos;
      glm::vec2   mouseWheelOffset;
   } ;

   class App{
   public:
      App();// Init all globals and AppData
      virtual ~App();
      void run();
   };
   //To be defind in client
   App* CreateApp();
};
