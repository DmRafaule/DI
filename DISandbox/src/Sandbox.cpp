#include "MyScene.hpp"
#include "Sandbox.hpp"
#include "Entry.hpp"

/*Inherit engine side App class*/
GET_GLOBAL_DATA
Sandbox::Sandbox(){   

    scene1 = C_Ref<MyScene>();
    DI::SceneHandler::Set("scene1",*scene1);
       
}
Sandbox::~Sandbox(){}


/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}
