#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:   
    Sandbox(){

        sh1 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh1,"res/shaders/Phong_dirLight(without_color).vert","res/shaders/Phong_dirLight(without_color).frag");
        
        model = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model,"res/models/3cubes.obj");
        for (int i = 0; i < model->meshes.size(); ++i){
            DI::MeshHandler::Set(*model->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_dirLight(without_color).vert");
            DI::MaterialHandler::SetShader(*model->materials[i],*sh1);
        }

        view1 = C_Ref<DI::View>();
        DI::ViewHandler::SetDefault(*view1,_winData->size);
    }
    ~Sandbox(){}

    void updateEvents_loop(SDL_Event& Event){
      
    }
    void updateRender_loop(){
        DI::ViewHandler::Use(*view1);

        // Draw geometry with flat material
        for (int i = 0; i < model->meshes.size(); ++i){
            model->meshes[i]->model_matrix = glm::mat4(1.0f);
            DI::MeshHandler::Translate(*model->meshes[i],glm::vec3(0.0f,0.0f,0.0f));
            DI::ShaderHandler::Use(*sh1);//HERE figure out how to make this look better
            *(static_cast<glm::mat4*>(model->materials[i]->uniforms["u_model"].first)) = model->meshes[i]->model_matrix;
            *(static_cast<glm::mat4*>(model->materials[i]->uniforms["u_proj"].first)) = view1->proj;
            *(static_cast<glm::mat4*>(model->materials[i]->uniforms["u_view"].first)) = view1->eye;
            *(static_cast<float*>(model->materials[i]->uniforms["u_time"].first)) = (float)DI::CoreTime::time_since_start_programm;
            *(static_cast<glm::vec3*>(model->materials[i]->uniforms["viewPos"].first)) = view1->pos;
            *(static_cast<float*>(model->materials[i]->uniforms["material.shininess"].first)) = (float)(0.7 * 128);
            *(static_cast<glm::vec3*>(model->materials[i]->uniforms["light.ambient"].first)) = glm::vec3(0.3f, 0.3f, 0.3f);
            *(static_cast<glm::vec3*>(model->materials[i]->uniforms["light.diffuse"].first)) = glm::vec3(0.5f, 0.5f, 0.5f);
            *(static_cast<glm::vec3*>(model->materials[i]->uniforms["light.specular"].first)) = glm::vec3(1.0f, 1.0f, 1.0f);
            *(static_cast<glm::vec3*>(model->materials[i]->uniforms["light.direction"].first)) = glm::vec3(_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);
            DI::MaterialHandler::UseMaterial(*model->materials[i],*sh1);
            
            
            DI::RenderHandler::DrawElements(*model->meshes[i]);
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