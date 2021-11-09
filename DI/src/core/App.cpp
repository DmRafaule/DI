#include "GL/glew.h"

#include "App.hpp"
#include "Log.hpp"

#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "AppEvent.hpp"
#include "KeyboardEvent.hpp"

namespace DI{

   App::App(){
      DI::Log::Init();
      DI_LOG_TRACE("Init App");
      WinHandler::WinInit();
   }
   App::~App(){
      WinHandler::WinKill();
      DI_LOG_TRACE("Kill app");
   }
   void App::run(){
      while(WinHandler::WinUpdate());
   }

};