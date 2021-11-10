#include "GL/glew.h"

#include "App.hpp"
#include "Win.hpp"
#include "Log.hpp"



namespace DI{

   extern WinData g_winData;

   App::App(){
      DI::Log::Init();
      DI_LOG_TRACE("Init App");
      _isRunning = true;
      WinHandler::WinInit();
   }
   App::~App(){
      DI_LOG_TRACE("Kill app");
   }
   void App::run(){
      while(g_winData.isOpen){
         WinHandler::WinEvUpdate();
         WinHandler::WinUpdate();
      }
   }
};