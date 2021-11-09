#pragma once
#include "Core.hpp"
#include "Win.hpp"

namespace DI{

   class App{
   public:
      App();
      virtual ~App();
      void run();
   private:
      bool     _isRunning = true;
   };
   //To be defind in client
   App* CreateApp();
};