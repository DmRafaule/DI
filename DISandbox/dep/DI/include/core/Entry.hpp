#pragma once 

#include "App.hpp"

extern DI::App* DI::CreateApp();

int main (int argc, char **argv){

   auto app = DI::CreateApp();
   app->run();
   delete app;
}