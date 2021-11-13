#include "DI.hpp"



/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:    
   Sandbox(){}
   ~Sandbox(){}

   void updateEvents_loop(SDL_Event& Event){
      
   }
   void updateRender_loop(){
       
   }
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}