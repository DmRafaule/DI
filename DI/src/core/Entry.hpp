#pragma once 

#include "App.hpp"
#include "Log.hpp"

extern DI::App* DI::CreateApp();

int main (int argc, char **argv){
   DI::Log::Init();
   DI_LOG_TRACE("Init Loggin system");
   DI_LOG_TRACE("Init App");

   auto app = DI::CreateApp();
   app->run();
   delete app;
}