#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:   
    Sandbox(){

        // Cube with flat color
        sh1 = C_Ref<DI::Shader>();
        model = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model,"res/models/snowSquare.obj");
        for (auto mesh : model->meshes){
            DI::MeshHandler::Set(*mesh);
            DI::LayoutHandler::Set("res/shaders/flatColor.vert");
        }
        DI::ShaderHandler::Set(*sh1,"res/shaders/flatColor.vert","res/shaders/flatColor.frag");





        view1 = C_Ref<DI::View>();
        DI::ViewHandler::SetDefault(*view1,_winData->size);
    }
    ~Sandbox(){}

    void updateEvents_loop(SDL_Event& Event){
      
    }
    void updateRender_loop(){
        DI::ViewHandler::Use(*view1);

        // Draw geometry with flat material
        for (auto mesh : model->meshes){
            mesh->model_matrix = glm::mat4(1.0f);
            DI::MeshHandler::Translate(*mesh,glm::vec3(10.0f,0.0f,0.0f));
            DI::ShaderHandler::Use(*sh1);
            DI::ShaderHandler::SetUniform(*sh1, "u_mvp",view1->proj * view1->eye * mesh->model_matrix);
            DI::ShaderHandler::SetUniform(*sh1, "u_time",(float)DI::CoreTime::time_since_start_programm);
            DI::RenderHandler::DrawElements(*mesh);
        }

    }
    void onKeyPressed(int key, bool isKey_repeat){
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
    void onMouseScrolled(glm::vec2 offset){
        if (isMouseActive)
            DI::ViewHandler::SetZoom(*view1,offset.y);
    }
    void onMouseMoved(glm::vec2 pos){
        if (isMouseActive)
            DI::ViewHandler::SetMotion(*view1,glm::vec2(pos.x,pos.y));
    }
private:
    bool isMouseActive = true;
    Ref<DI::Shader>     sh1;
    Ref<DI::Model>      model;
    Ref<DI::View>       view1;
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}