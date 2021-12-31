#pragma once 

#include "DI.hpp"

class MyScene;
class Sandbox : public DI::App{
public:   
   Sandbox();
   ~Sandbox();
private:
   Ref<MyScene>      scene1;
   
};
