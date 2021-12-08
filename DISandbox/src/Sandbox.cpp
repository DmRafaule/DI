#include "DI.hpp"

/*Inherit engine side App class*/
class Sandbox : public DI::App{
public:   
    Sandbox(){
        view1 = C_Ref<DI::View>();
        DI::ViewHandler::SetDefault(*view1,_winData->size);


        sh1 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh1,"res/shaders/Phong_dirLight(without_color).vert","res/shaders/Phong_dirLight(without_color).frag");
        sh2 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh2,"res/shaders/Phong_DirPointSpotLight.vert","res/shaders/Phong_DirPointSpotLight.frag");
        sh3 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh3,"res/shaders/flatColor.vert","res/shaders/flatColor.frag");
        sh4 = C_Ref<DI::Shader>();
        DI::ShaderHandler::Set(*sh4,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");

        model1 = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model1,"res/models/3cubes/3cubes.obj");
        for (int i = 0; i < model1->meshes.size(); ++i){
            DI::MeshHandler::Set(*model1->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_dirLight(without_color).vert");
            DI::MaterialHandler::SetShader(*model1->materials[i],*sh1);
            // This data must be assigned when read model1(most of them)
            model1->materials[i]->uniforms["u_model"].first = &model1->meshes[i]->model_matrix;
            model1->materials[i]->uniforms["u_proj"].first  = &view1->proj;
            model1->materials[i]->uniforms["u_view"].first  = &view1->eye;
            model1->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
            model1->materials[i]->uniforms["viewPos"].first = &view1->pos;
            
            model1->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
            model1->materials[i]->uniforms["light.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model1->materials[i]->uniforms["light.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model1->materials[i]->uniforms["light.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model1->materials[i]->uniforms["light.direction"].first = &_imguiData->vslot1;
        }
        
        model2 = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model2,"res/models/sphereEarth/sphere.dae");
        for (int i = 0; i < model2->meshes.size(); ++i){
            DI::MeshHandler::Set(*model2->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLight.vert");
            DI::MaterialHandler::SetShader(*model2->materials[i],*sh2);
            // This data must be assigned when read model2(most of them)
            model2->materials[i]->uniforms["u_model"].first = &model2->meshes[i]->model_matrix;
            model2->materials[i]->uniforms["u_proj"].first  = &view1->proj;
            model2->materials[i]->uniforms["u_view"].first  = &view1->eye;
            model2->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
            model2->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
            model2->materials[i]->uniforms["viewPos"].first = &view1->pos;
           
            model2->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model2->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model2->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model2->materials[i]->uniforms["dirLight.direction"].first = &_imguiData->vslot1;

            model2->materials[i]->uniforms["pointLights.position"].first = &_imguiData->vslot2;
            model2->materials[i]->uniforms["pointLights.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model2->materials[i]->uniforms["pointLights.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model2->materials[i]->uniforms["pointLights.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model2->materials[i]->uniforms["pointLights.constant"].first = new float(1.0f);
            model2->materials[i]->uniforms["pointLights.linear"].first = new float(0.09f);
            model2->materials[i]->uniforms["pointLights.quadratic"].first = new float(0.032f);


            model2->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);
            model2->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model2->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
            model2->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
            model2->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model2->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model2->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model2->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
            model2->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
            model2->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

            model2->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
        }
        
        model3 = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model3,"res/models/cube/cube.ply");
        for (int i = 0; i < model3->meshes.size(); ++i){
            DI::MeshHandler::Set(*model3->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_dirLight(without_color).vert");
            DI::MaterialHandler::SetShader(*model3->materials[i],*sh3);
            // This data must be assigned when read model1(most of them)
            model3->materials[i]->uniforms["u_model"].first = &model3->meshes[i]->model_matrix;
            model3->materials[i]->uniforms["u_proj"].first  = &view1->proj;
            model3->materials[i]->uniforms["u_view"].first  = &view1->eye;
            model3->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        }
        
        model4 = C_Ref<DI::Model>();
        DI::ModelHandler::Load(*model4,"res/models/sphereEarth/sphere.dae");
        for (int i = 0; i < model4->meshes.size(); ++i){
            DI::MeshHandler::Set(*model4->meshes[i]);
            DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
            DI::MaterialHandler::SetShader(*model4->materials[i],*sh4);
            model4->materials[i]->uniforms["u_model"].first = &model4->meshes[i]->model_matrix;
            model4->materials[i]->uniforms["u_proj"].first  = &view1->proj;
            model4->materials[i]->uniforms["u_view"].first  = &view1->eye;
            model4->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
            model4->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
            model4->materials[i]->uniforms["viewPos"].first = &view1->pos;
           
            model4->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model4->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model4->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model4->materials[i]->uniforms["dirLight.direction"].first = &_imguiData->vslot1;

            model4->materials[i]->uniforms["pointLights.position"].first = &_imguiData->vslot2;
            model4->materials[i]->uniforms["pointLights.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model4->materials[i]->uniforms["pointLights.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model4->materials[i]->uniforms["pointLights.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model4->materials[i]->uniforms["pointLights.constant"].first = new float(1.0f);
            model4->materials[i]->uniforms["pointLights.linear"].first = new float(0.09f);
            model4->materials[i]->uniforms["pointLights.quadratic"].first = new float(0.032f);


            model4->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);
            model4->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model4->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
            model4->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
            model4->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
            model4->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
            model4->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
            model4->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
            model4->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
            model4->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

            model4->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
        }
            
    }
    ~Sandbox(){}

    void updateEvents_loop(SDL_Event& Event){
      
    }
    void updateRender_loop(){
        DI::ViewHandler::Use(*view1);

        DI::RenderHandler::Draw(*model1,*sh1);

        DI::ModelHandler::Translate(*model2,glm::vec3(5.0f,0.0f,0.0f));
        DI::RenderHandler::Draw(*model2,*sh2);
        
        DI::ModelHandler::Translate(*model3,glm::vec3(-5.0f,0.0f,0.0f));
        DI::RenderHandler::Draw(*model3,*sh3);

        DI::ModelHandler::Translate(*model4,glm::vec3(5.0f,5.0f,0.0f));
        DI::RenderHandler::Draw(*model4,*sh4);


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
    Ref<DI::Shader>     sh2;
    Ref<DI::Shader>     sh3;
    Ref<DI::Shader>     sh4;
    Ref<DI::Model>      model1;
    Ref<DI::Model>      model2;
    Ref<DI::Model>      model3;
    Ref<DI::Model>      model4;
    Ref<DI::View>       view1;
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}