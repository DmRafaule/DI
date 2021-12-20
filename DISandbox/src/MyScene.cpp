#include "MyScene.hpp"

GET_GLOBAL_DATA

MyScene::MyScene(){
    DI::EventsHandler::Set(DI::EventType::KEY_PRESSED,std::bind(&MyScene::KeyPressed,this,std::placeholders::_1,std::placeholders::_2));
    DI::EventsHandler::Set(DI::EventType::MOUSE_SCROLLED,std::bind(&MyScene::MouseScrolled,this,std::placeholders::_1));
    DI::EventsHandler::Set(DI::EventType::MOUSE_MOVED,std::bind(&MyScene::MouseMoved,this,std::placeholders::_1));
    DI::LayerHandler::Set("RenderScene",0,std::bind(&MyScene::RenderScene,this),layers);

    view1 = C_Ref<DI::View>();
    DI::ViewHandler::SetDefault(*view1,DI::_winData->size);

    
}
MyScene::~MyScene(){

}
void MyScene::RenderScene(){
    DI::ViewHandler::Use(*view1);


}
void MyScene::KeyPressed(int key, bool isKey_repeat){
    switch(key){
        case SDL_KeyCode::SDLK_w:{
            DI::ViewHandler::SetPos(*view1,view1->pos + 1.f * view1->front);
            break;
        }
        case SDL_KeyCode::SDLK_s:{
            DI::ViewHandler::SetPos(*view1,view1->pos - 1.f * view1->front);
            break;
        }
        case SDL_KeyCode::SDLK_a:{
            DI::ViewHandler::SetPos(*view1,view1->pos - glm::normalize(glm::cross(view1->front,view1->up)) * 1.f);
            break;
        }
        case SDL_KeyCode::SDLK_d:{
            DI::ViewHandler::SetPos(*view1,view1->pos + glm::normalize(glm::cross(view1->front,view1->up)) * 1.f);
            break;
        }
        case SDL_KeyCode::SDLK_ESCAPE:{
            if (isMouseActive)
                isMouseActive = false;
            else
                isMouseActive = true;
            break;
        }
    }
}
void MyScene::MouseScrolled(glm::vec2 offset){
    if (isMouseActive)
        DI::ViewHandler::SetZoom(*view1,offset.y);
}
void MyScene::MouseMoved(glm::vec2 pos){
    if (isMouseActive)
        DI::ViewHandler::SetMotion(*view1,glm::vec2(pos.x,pos.y));
}
