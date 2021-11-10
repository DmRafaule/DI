#pragma once
#include "Core.hpp"

namespace DI{


   class App{
   public:
      App();
      virtual ~App();
      void run();
   private:
      bool _isRunning;
   };
   //To be defind in client
   App* CreateApp();
};