#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:    
    Sandbox(){
        
    }
    ~Sandbox(){

    }
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}