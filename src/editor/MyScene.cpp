#include "MyScene.hpp"

GET_GLOBAL_DATA

MyScene::MyScene(){
    DI::EventsHandler::Set(DI::EventType::KEY_PRESSED,std::bind(&MyScene::KeyPressed,this,std::placeholders::_1,std::placeholders::_2));
    DI::EventsHandler::Set(DI::EventType::MOUSE_SCROLLED,std::bind(&MyScene::MouseScrolled,this,std::placeholders::_1));
    DI::EventsHandler::Set(DI::EventType::MOUSE_MOVED,std::bind(&MyScene::MouseMoved,this,std::placeholders::_1));
    DI::LayerHandler::Set("RenderScene",0,std::bind(&MyScene::RenderScene,this),layers);

    view1 = C_Scope<DI::View>();
    DI::ViewHandler::SetDefault(*view1,DI::_guiData->mainViewport_size);
    shader = C_Scope<DI::Shader>();
    DI::ShaderHandler::Set(*shader,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");
    shader1 = C_Scope<DI::Shader>();
    DI::ShaderHandler::Set(*shader1,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");
    shader2 = C_Scope<DI::Shader>();
    DI::ShaderHandler::Set(*shader2,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");

    simpleSphere = C_Scope<DI::Model>();
    DI::ModelHandler::Load(*simpleSphere,"res/models/sphereEarth/sphere.dae");
    for (int i = 0; i < simpleSphere->meshes.size(); ++i){
        DI::MeshHandler::Set(*simpleSphere->meshes[i]);// Here load too many meshes
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*simpleSphere->materials[i],*shader);
        // This data must be assigned when read earth(most of them)
        simpleSphere->materials[i]->uniforms["u_model"].first = &simpleSphere->meshes[i]->model_matrix;
        simpleSphere->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        simpleSphere->materials[i]->uniforms["u_view"].first  = &view1->eye;
        simpleSphere->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        simpleSphere->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        simpleSphere->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        simpleSphere->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        simpleSphere->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        simpleSphere->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        simpleSphere->materials[i]->uniforms["dirLight.direction"].first = new glm::vec3(1.1f, 1.1f, -3.1f);

        simpleSphere->materials[i]->uniforms["pointLights.position"].first   = new glm::vec3(1.1f, 1.1f, -3.1f);
        simpleSphere->materials[i]->uniforms["pointLights.ambient"].first    = new glm::vec3(0.1f, 0.1f, 0.1f);
        simpleSphere->materials[i]->uniforms["pointLights.diffuse"].first    = new glm::vec3(0.6f, 0.6f, 0.6f);
        simpleSphere->materials[i]->uniforms["pointLights.specular"].first   = new glm::vec3(0.77f, 0.5f, 0.9f);
        simpleSphere->materials[i]->uniforms["pointLights.constant"].first   = new float(1.0f);
        simpleSphere->materials[i]->uniforms["pointLights.linear"].first     = new float(0.0f);
        simpleSphere->materials[i]->uniforms["pointLights.quadratic"].first  = new float(0.0f);


        simpleSphere->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(0.0f,0.0f,0.0f);
        simpleSphere->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        simpleSphere->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        simpleSphere->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        simpleSphere->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        simpleSphere->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        simpleSphere->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        simpleSphere->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        simpleSphere->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        simpleSphere->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        simpleSphere->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }
    
    cubes = C_Scope<DI::Model>();
    DI::ModelHandler::Load(*cubes,"res/models/3cubes/3cubes.obj");
    for (int i = 0; i < cubes->meshes.size(); ++i){
        DI::MeshHandler::Set(*cubes->meshes[i]);// Here load too many meshes
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*cubes->materials[i],*shader);
        // This data must be assigned when read earth(most of them)
        cubes->materials[i]->uniforms["u_model"].first = &cubes->meshes[i]->model_matrix;
        cubes->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        cubes->materials[i]->uniforms["u_view"].first  = &view1->eye;
        cubes->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        cubes->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        cubes->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        cubes->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        cubes->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        cubes->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        cubes->materials[i]->uniforms["dirLight.direction"].first = new glm::vec3(1.1f, 1.1f, -3.1f);

        cubes->materials[i]->uniforms["pointLights.position"].first   = new glm::vec3(1.1f, 1.1f, -3.1f);
        cubes->materials[i]->uniforms["pointLights.ambient"].first    = new glm::vec3(0.1f, 0.1f, 0.1f);
        cubes->materials[i]->uniforms["pointLights.diffuse"].first    = new glm::vec3(0.6f, 0.6f, 0.6f);
        cubes->materials[i]->uniforms["pointLights.specular"].first   = new glm::vec3(0.77f, 0.5f, 0.9f);
        cubes->materials[i]->uniforms["pointLights.constant"].first   = new float(1.0f);
        cubes->materials[i]->uniforms["pointLights.linear"].first     = new float(0.0f);
        cubes->materials[i]->uniforms["pointLights.quadratic"].first  = new float(0.0f);


        cubes->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(0.0f,0.0f,0.0f);
        cubes->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        cubes->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        cubes->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        cubes->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        cubes->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        cubes->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        cubes->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        cubes->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        cubes->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        cubes->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

}
MyScene::~MyScene(){

}
void MyScene::RenderScene(){
    DI::ViewHandler::Use(*view1);

    DI::ModelHandler::Translate(*simpleSphere,glm::vec3(5.0f,0.0f,0.0f));
    DI::ModelHandler::Rotate(*simpleSphere,DI::CoreTime::time_since_start_programm * 5.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*simpleSphere,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::RenderHandler::Draw(*simpleSphere,*shader);
    DI::RenderHandler::Draw(*cubes,*shader);


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
