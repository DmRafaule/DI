#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:   
    Sandbox(){
        view1 = C_Ref<DI::View>();
        DI::ViewHandler::SetDefault(*view1,_winData->size);


        sh1 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh1,"res/shaders/Phong_dirLight(without_color).vert","res/shaders/Phong_dirLight(without_color).frag");
        
        model = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model,"res/models/3cubes.obj");
        for (int i = 0; i < model->meshes.size(); ++i){
            DI::MeshHandler::Set(*model->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_dirLight(without_color).vert");
            DI::MaterialHandler::SetShader(*model->materials[i],*sh1);
            // This data must be assigned when read model(most of them)
            model->materials[i]->uniforms["u_model"].first = &model->meshes[i]->model_matrix;
            model->materials[i]->uniforms["u_proj"].first  = &view1->proj;
            model->materials[i]->uniforms["u_view"].first  = &view1->eye;
            model->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
            model->materials[i]->uniforms["viewPos"].first = &view1->pos;
            
            model->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
            model->materials[i]->uniforms["light.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model->materials[i]->uniforms["light.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model->materials[i]->uniforms["light.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model->materials[i]->uniforms["light.direction"].first = new glm::vec3(_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);
        }
            
            

    }
    ~Sandbox(){}

    void updateEvents_loop(SDL_Event& Event){
      
    }
    void updateRender_loop(){
        DI::ViewHandler::Use(*view1);
        DI::ModelHandler::Use(*model,*sh1);
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