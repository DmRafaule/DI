#include "DI.hpp"


/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:    
    Sandbox(){
        m1 = new DI::Mesh();
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
        DI::LayoutHandler::Set("res/simpleColor.vert");
             
        m2 = new DI::Mesh();
        m2->verticies.count = 24;
        m2->verticies.data = new float[m2->verticies.count]{
             0.5f, 0.5f,  0.5f, 
             0.5f,-0.5f,  0.5f, 
            -0.5f,-0.5f,  0.5f,
            -0.5f, 0.5f,  0.5f,
             0.5f, 0.5f, -0.5f, 
             0.5f,-0.5f, -0.5f, 
            -0.5f,-0.5f, -0.5f, 
            -0.5f, 0.5f, -0.5f, 
        };
        m2->elements.count = 36;
        m2->elements.data = new unsigned int[m2->elements.count]{
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
        DI::MeshHandler::Set(*m2);
        DI::LayoutHandler::Set("res/simpleColor.vert");
             
    
        

        sh1   = new DI::Shader();
        tx1   = new DI::Texture();
        view1 = new DI::View();
        
        DI::TextureHandler::Set(*tx1,std::vector<std::string>({"res/meeting-guwei.jpg"}),std::vector<uint>({GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER,GL_NEAREST,GL_NEAREST}));
        DI::ShaderHandler::Set(*sh1,"res/simpleColor.vert","res/simpleColor.frag");
        DI::ViewHandler::SetDefault(*view1,_winData.size);
    }
    ~Sandbox(){}

    void updateEvents_loop(SDL_Event& Event){
      
    }
    void updateRender_loop(){
        DI::ShaderHandler::Use(*sh1);
        DI::TextureHandler::Use(*tx1,*sh1);
        DI::ViewHandler::Use(*view1);
        DI::ShaderHandler::SetUniform(*sh1, "u_mvp",view1->proj * view1->eye * m1->model_matrix);
        DI::ShaderHandler::SetUniform(*sh1, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::RenderHandler::Draw(*m1);

        DI::MeshHandler::Translate(*m1,glm::vec3(10.f,0.f,0.f));
        DI::ShaderHandler::SetUniform(*sh1, "u_mvp",view1->proj * view1->eye * m2->model_matrix);
        DI::ShaderHandler::SetUniform(*sh1, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::RenderHandler::Draw(*m2);
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
        }
    }
    void onMouseScrolled(glm::vec2 offset){
        DI::ViewHandler::SetZoom(*view1,offset.y);
    }
    void onMouseMoved(glm::vec2 pos){
        DI::ViewHandler::SetMotion(*view1,glm::vec2(pos.x,pos.y));
    }
private:
    DI::Mesh            *m1;
    DI::Mesh            *m2;
    DI::Shader          *sh1;
    DI::View            *view1;
    DI::Texture         *tx1;
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}