#include "MyScene.hpp"

GET_GLOBAL_DATA

MyScene::MyScene(){
    DI::EventsHandler::Set(DI::EventType::KEY_PRESSED,std::bind(&MyScene::KeyPressed,this,std::placeholders::_1,std::placeholders::_2));
    DI::EventsHandler::Set(DI::EventType::MOUSE_SCROLLED,std::bind(&MyScene::MouseScrolled,this,std::placeholders::_1));
    DI::EventsHandler::Set(DI::EventType::MOUSE_MOVED,std::bind(&MyScene::MouseMoved,this,std::placeholders::_1));
    DI::LayerHandler::Set("RenderScene",0,std::bind(&MyScene::RenderScene,this),layers);
    DI_LOG_TRACE("Init scene");
    DI::_winData->bg = glm::vec3(0.0f,0.0f,0.0f);
    view1 = C_Ref<DI::View>();
    DI::ViewHandler::SetDefault(*view1,DI::_winData->size);

    sh1 = C_Ref<DI::Shader>();
    DI::ShaderHandler::Set(*sh1,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");
    sol_shader = C_Ref<DI::Shader>();
    DI::ShaderHandler::Set(*sol_shader,"res/shaders/Phong_DirPointSpotLightTexture.vert","res/shaders/Phong_DirPointSpotLightTexture.frag");

    mars = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*mars,"res/models/sphereMars/sphere.dae");
    for (int i = 0; i < mars->meshes.size(); ++i){
        DI::MeshHandler::Set(*mars->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*mars->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        mars->materials[i]->uniforms["u_model"].first = &mars->meshes[i]->model_matrix;
        mars->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        mars->materials[i]->uniforms["u_view"].first  = &view1->eye;
        mars->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        mars->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        mars->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        mars->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        mars->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        mars->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        mars->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        mars->materials[i]->uniforms["pointLights.position"].first   = &DI::_imguiData->pointPos;
        mars->materials[i]->uniforms["pointLights.ambient"].first    = &DI::_imguiData->ambient;
        mars->materials[i]->uniforms["pointLights.diffuse"].first    = &DI::_imguiData->diffuse;
        mars->materials[i]->uniforms["pointLights.specular"].first   = &DI::_imguiData->specular;
        mars->materials[i]->uniforms["pointLights.constant"].first   = &DI::_imguiData->constant;
        mars->materials[i]->uniforms["pointLights.linear"].first     = &DI::_imguiData->linear;
        mars->materials[i]->uniforms["pointLights.quadratic"].first  = &DI::_imguiData->quadratic;


        mars->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        mars->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        mars->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        mars->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        mars->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        mars->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        mars->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        mars->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        mars->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        mars->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        mars->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

    earth = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*earth,"res/models/sphereEarth/sphere.dae");
    for (int i = 0; i < earth->meshes.size(); ++i){
        DI::MeshHandler::Set(*earth->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*earth->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        earth->materials[i]->uniforms["u_model"].first = &earth->meshes[i]->model_matrix;
        earth->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        earth->materials[i]->uniforms["u_view"].first  = &view1->eye;
        earth->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        earth->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        earth->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        earth->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        earth->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        earth->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        earth->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        earth->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        earth->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        earth->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        earth->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        earth->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        earth->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        earth->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        earth->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        earth->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        earth->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        earth->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        earth->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        earth->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        earth->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        earth->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        earth->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        earth->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        earth->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

    moon = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*moon,"res/models/moon/moon.dae");
    for (int i = 0; i < moon->meshes.size(); ++i){
        DI::MeshHandler::Set(*moon->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*moon->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        moon->materials[i]->uniforms["u_model"].first = &moon->meshes[i]->model_matrix;
        moon->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        moon->materials[i]->uniforms["u_view"].first  = &view1->eye;
        moon->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        moon->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        moon->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        moon->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        moon->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        moon->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        moon->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        moon->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        moon->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        moon->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        moon->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        moon->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        moon->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        moon->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        moon->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        moon->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        moon->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        moon->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        moon->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        moon->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        moon->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        moon->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        moon->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        moon->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        moon->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

    sol = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*sol,"res/models/sol/sol.dae");
    for (int i = 0; i < sol->meshes.size(); ++i){
        DI::MeshHandler::Set(*sol->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*sol->materials[i],*sol_shader);
        // This data must be assigned when read earth(most of them)
        sol->materials[i]->uniforms["u_model"].first = &sol->meshes[i]->model_matrix;
        sol->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        sol->materials[i]->uniforms["u_view"].first  = &view1->eye;
        sol->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        sol->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        sol->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        sol->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        sol->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        sol->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        sol->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        sol->materials[i]->uniforms["pointLights.position"].first = new glm::vec3(0.0f, 0.0f, 0.0f);
        sol->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient_;
        sol->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse_;
        sol->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular_;
        sol->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant_;
        sol->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear_;
        sol->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic_;


        sol->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        sol->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        sol->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        sol->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        sol->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        sol->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        sol->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        sol->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        sol->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        sol->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        sol->materials[i]->uniforms["material.shininess"].first = &DI::_imguiData->shineness_;
    }
     
    jupiter = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*jupiter,"res/models/jupiter/jupiter.dae");
    for (int i = 0; i < jupiter->meshes.size(); ++i){
        DI::MeshHandler::Set(*jupiter->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*jupiter->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        jupiter->materials[i]->uniforms["u_model"].first = &jupiter->meshes[i]->model_matrix;
        jupiter->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        jupiter->materials[i]->uniforms["u_view"].first  = &view1->eye;
        jupiter->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        jupiter->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        jupiter->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        jupiter->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        jupiter->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        jupiter->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        jupiter->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        jupiter->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        jupiter->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        jupiter->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        jupiter->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        jupiter->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        jupiter->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        jupiter->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        jupiter->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        jupiter->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        jupiter->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        jupiter->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        jupiter->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        jupiter->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        jupiter->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        jupiter->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        jupiter->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        jupiter->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        jupiter->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }
    
    io = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*io,"res/models/Io/Io.dae");
    for (int i = 0; i < io->meshes.size(); ++i){
        DI::MeshHandler::Set(*io->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*io->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        io->materials[i]->uniforms["u_model"].first = &io->meshes[i]->model_matrix;
        io->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        io->materials[i]->uniforms["u_view"].first  = &view1->eye;
        io->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        io->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        io->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        io->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        io->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        io->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        io->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        io->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        io->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        io->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        io->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        io->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        io->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        io->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        io->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        io->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        io->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        io->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        io->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        io->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        io->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        io->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        io->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        io->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        io->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

    kalisto = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*kalisto,"res/models/Kalisto/kalisto.dae");
    for (int i = 0; i < kalisto->meshes.size(); ++i){
        DI::MeshHandler::Set(*kalisto->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*kalisto->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        kalisto->materials[i]->uniforms["u_model"].first = &kalisto->meshes[i]->model_matrix;
        kalisto->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        kalisto->materials[i]->uniforms["u_view"].first  = &view1->eye;
        kalisto->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        kalisto->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        kalisto->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        kalisto->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.1f, 0.1f, 0.1f);
        kalisto->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        kalisto->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        kalisto->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        kalisto->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        kalisto->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        kalisto->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        kalisto->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        kalisto->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        kalisto->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        kalisto->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        kalisto->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        kalisto->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        kalisto->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        kalisto->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        kalisto->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        kalisto->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        kalisto->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        kalisto->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        kalisto->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        kalisto->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        kalisto->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

    europe = C_Ref<DI::Model>();
    DI::ModelHandler::Load(*europe,"res/models/europe/europe.dae");
    for (int i = 0; i < europe->meshes.size(); ++i){
        DI::MeshHandler::Set(*europe->meshes[i]);
        DI::LayoutHandler::Set("res/shaders/Phong_DirPointSpotLightTexture.vert");
        DI::MaterialHandler::SetShader(*europe->materials[i],*sh1);
        // This data must be assigned when read earth(most of them)
        europe->materials[i]->uniforms["u_model"].first = &europe->meshes[i]->model_matrix;
        europe->materials[i]->uniforms["u_proj"].first  = &view1->proj;
        europe->materials[i]->uniforms["u_view"].first  = &view1->eye;
        europe->materials[i]->uniforms["u_color"].first  = new glm::vec3(0.5f, 0.32f, 0.7119f);
        europe->materials[i]->uniforms["u_time"].first  = &DI::CoreTime::time_since_start_programm;
        europe->materials[i]->uniforms["viewPos"].first = &view1->pos;
        
        europe->materials[i]->uniforms["dirLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        europe->materials[i]->uniforms["dirLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        europe->materials[i]->uniforms["dirLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        europe->materials[i]->uniforms["dirLight.direction"].first = &DI::_imguiData->vslot1;

        europe->materials[i]->uniforms["pointLights.position"].first = &DI::_imguiData->pointPos;
        europe->materials[i]->uniforms["pointLights.ambient"].first = &DI::_imguiData->ambient;
        europe->materials[i]->uniforms["pointLights.diffuse"].first = &DI::_imguiData->diffuse;
        europe->materials[i]->uniforms["pointLights.specular"].first = &DI::_imguiData->specular;
        europe->materials[i]->uniforms["pointLights.constant"].first = &DI::_imguiData->constant;
        europe->materials[i]->uniforms["pointLights.linear"].first = &DI::_imguiData->linear;
        europe->materials[i]->uniforms["pointLights.quadratic"].first = &DI::_imguiData->quadratic;


        europe->materials[i]->uniforms["spotLight.direction"].first = new glm::vec3(DI::_imguiData->slot0, DI::_imguiData->slot1, DI::_imguiData->slot2);
        europe->materials[i]->uniforms["spotLight.position"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        europe->materials[i]->uniforms["spotLight.cutOff"].first = new float(0.5f);
        europe->materials[i]->uniforms["spotLight.outerCutOff"].first = new float(0.6f);
        europe->materials[i]->uniforms["spotLight.ambient"].first = new glm::vec3(0.3f, 0.3f, 0.3f);
        europe->materials[i]->uniforms["spotLight.diffuse"].first = new glm::vec3(0.5f, 0.5f, 0.5f);
        europe->materials[i]->uniforms["spotLight.specular"].first = new glm::vec3(1.0f, 1.0f, 1.0f);
        europe->materials[i]->uniforms["spotLight.constant"].first = new float(1.0f);
        europe->materials[i]->uniforms["spotLight.linear"].first = new float(0.09f);
        europe->materials[i]->uniforms["spotLight.quadratic"].first = new float(0.032f);

        europe->materials[i]->uniforms["material.shininess"].first = new float(0.7 * 128);
    }

}
MyScene::~MyScene(){
   DI_LOG_TRACE("Remove scene");  
}
void MyScene::RenderScene(){
    DI::ViewHandler::Use(*view1);

    
    DI::ModelHandler::Translate(*sol,glm::vec3(0.0f,5.0f,0.0f));
    DI::ModelHandler::Rotate(*sol,DI::CoreTime::time_since_start_programm,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*sol,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*sol,glm::vec3(5.0f));
    DI::RenderHandler::Draw(*sol,*sol_shader);

    
    DI::ModelHandler::Translate(*mars,glm::vec3(cos(DI::CoreTime::time_since_start_programm*0.8f) * 30.0f ,0.0f,sin(DI::CoreTime::time_since_start_programm*0.8f)*30.0f));
    DI::ModelHandler::Rotate(*mars,DI::CoreTime::time_since_start_programm * 25.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*mars,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*mars,glm::vec3(0.8f));
    DI::RenderHandler::Draw(*mars,*sh1);

    DI::ModelHandler::Translate(*earth,glm::vec3(cos(DI::CoreTime::time_since_start_programm) * 20.0f ,0.0f,sin(DI::CoreTime::time_since_start_programm)*20.0f));
    DI::ModelHandler::Rotate(*earth,DI::CoreTime::time_since_start_programm*15.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*earth,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::RenderHandler::Draw(*earth,*sh1);

    DI::ModelHandler::Translate(*moon,glm::vec3(cos(DI::CoreTime::time_since_start_programm) * 20.0f + cos(DI::CoreTime::time_since_start_programm) * 5.0f,0.0f,sin(DI::CoreTime::time_since_start_programm)*20.0f + sin(DI::CoreTime::time_since_start_programm) * 5.0f));
    DI::ModelHandler::Rotate(*moon,DI::CoreTime::time_since_start_programm * 25.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*moon,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*moon,glm::vec3(0.3f));
    DI::RenderHandler::Draw(*moon,*sh1);

    DI::ModelHandler::Translate(*jupiter,glm::vec3(cos(DI::CoreTime::time_since_start_programm*0.1f) * 75.0f ,0.0f,sin(DI::CoreTime::time_since_start_programm*0.1f)*75.0f));
    DI::ModelHandler::Rotate(*jupiter,DI::CoreTime::time_since_start_programm*15.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*jupiter,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::RenderHandler::Draw(*jupiter,*sh1);

    DI::ModelHandler::Translate(*io,glm::vec3(cos(DI::CoreTime::time_since_start_programm * 0.1f) * 75.0f + cos(DI::CoreTime::time_since_start_programm*8.0f) * 5.0f,0.0f,sin(DI::CoreTime::time_since_start_programm * 0.1)*75.0f + sin(DI::CoreTime::time_since_start_programm*8.0f) * 5.0f));
    DI::ModelHandler::Rotate(*io,DI::CoreTime::time_since_start_programm * 25.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*io,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*io,glm::vec3(0.3f));
    DI::RenderHandler::Draw(*io,*sh1);

    DI::ModelHandler::Translate(*kalisto,glm::vec3(cos(DI::CoreTime::time_since_start_programm * 0.1f) * 75.0f + cos(DI::CoreTime::time_since_start_programm*4.0f) * 10.0f,0.0f,sin(DI::CoreTime::time_since_start_programm * 0.1)*75.0f + sin(DI::CoreTime::time_since_start_programm*4.0f) * 10.0f));
    DI::ModelHandler::Rotate(*kalisto,DI::CoreTime::time_since_start_programm * 15.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*kalisto,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*kalisto,glm::vec3(0.3f));
    DI::RenderHandler::Draw(*kalisto,*sh1);

    DI::ModelHandler::Translate(*europe,glm::vec3(cos(DI::CoreTime::time_since_start_programm * 0.1f) * 75.0f + cos(DI::CoreTime::time_since_start_programm*2.0f) * 15.0f,0.0f,sin(DI::CoreTime::time_since_start_programm * 0.1)*75.0f + sin(DI::CoreTime::time_since_start_programm*2.0f) * 15.0f));
    DI::ModelHandler::Rotate(*europe,DI::CoreTime::time_since_start_programm * 5.0f,glm::vec3(0.0f,1.0f,0.0f));
    DI::ModelHandler::Rotate(*europe,90.0f,glm::vec3(1.0f,0.0f,0.0f));
    DI::ModelHandler::Scale(*europe,glm::vec3(0.3f));
    DI::RenderHandler::Draw(*europe,*sh1);


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
