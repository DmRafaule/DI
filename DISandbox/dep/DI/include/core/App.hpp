#pragma once
#include "Core.hpp"

namespace DI{
   class App{
   public:
      App();
      virtual ~App();
      void run();
   };
   //To be defind in client
   App* CreateApp();
};