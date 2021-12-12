#include "MyScene.hpp"
#include "Sandbox.hpp"
#include "Entry.hpp"

/*Inherit engine side App class*/
namespace DI{
    extern Scope<DI::AppData> _appData;
    extern Scope<DI::WinData> _winData;
    extern Scope<DI::ImGUIData> _imguiData;
}
Sandbox::Sandbox(){   

    scene1 = C_Ref<MyScene>();
    DI::SceneHandler::Set("scene1",*scene1);
       
}
Sandbox::~Sandbox(){}


/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}
