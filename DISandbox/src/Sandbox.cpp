#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:   
    Sandbox(){

        // Cube with flat color
        sh1 = C_Ref<DI::Shader>();
        m1 = C_Ref<DI::Mesh>();
        m1->verticies.count = 24;
        m1->verticies.data = new float[m1->verticies.count]{
             0.5f, 0.5f,  0.5f, 
             0.5f,-0.5f,  0.5f, 
            -0.5f,-0.5f,  0.5f,
            -0.5f, 0.5f,  0.5f,
             0.5f, 0.5f, -0.5f, 
             0.5f,-0.5f, -0.5f, 
            -0.5f,-0.5f, -0.5f, 
            -0.5f, 0.5f, -0.5f, 
        };
        m1->elements.count = 36;
        m1->elements.data = new unsigned int[m1->elements.count]{
            0,1,3,//Front face
            1,2,3,
    
            0,1,4,//Right-side face
            1,5,4,
    
            3,2,7,//Left-side face
            2,6,7,
    
            2,1,6,//Bottom face
            1,6,5,
    
            0,3,7,//Top face
            0,7,4,
    
            4,5,7,//Back face
            7,5,6,
        };
        DI::MeshHandler::Set(*m1);
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
        m1->model_matrix = glm::mat4(1.0f);
        DI::MeshHandler::Translate(*m1,glm::vec3(10.0f,0.0f,0.0f));
        DI::ShaderHandler::Use(*sh1);
        DI::ShaderHandler::SetUniform(*sh1, "u_mvp",view1->proj * view1->eye * m1->model_matrix);
        DI::ShaderHandler::SetUniform(*sh1, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::RenderHandler::DrawElements(*m1);

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
    Ref<DI::Mesh>       m1;
    Ref<DI::Shader>     sh1;
    Ref<DI::View>       view1;
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}