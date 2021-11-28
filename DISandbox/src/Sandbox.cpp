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
        
        // Cube affected to dirLight
        sh2 = C_Ref<DI::Shader>();
        m2 = C_Ref<DI::Mesh>();
        m2->verticies.count = 396;
        m2->verticies.data = new float[m2->verticies.count]{
            //Pos               //Col                   // Norm                 //Tex
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
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
        DI::ShaderHandler::Set(*sh2,"res/shaders/dirLight.vert","res/shaders/dirLight.frag");

        // Cube affected to point lighting
        sh3 = C_Ref<DI::Shader>();
        m3 = C_Ref<DI::Mesh>();
        m3->verticies.count = 396;
        m3->verticies.data = new float[m3->verticies.count]{
                //Pos               //Col                   // Norm                 //Tex
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
        };
        m3->elements.count = 36;
        m3->elements.data = new unsigned int[m3->elements.count]{
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
        DI::MeshHandler::Set(*m3);
        DI::ShaderHandler::Set(*sh3,"res/shaders/pointLight.vert","res/shaders/pointLight.frag");

        // Cube affected to spot light
        m4 = C_Ref<DI::Mesh>();
        sh4 = C_Ref<DI::Shader>();
        m4->verticies.count = 396;
        m4->verticies.data = new float[m4->verticies.count]{
                //Pos               //Col                   // Norm                 //Tex
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
        };
        m4->elements.count = 36;
        m4->elements.data = new unsigned int[m4->elements.count]{
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
        DI::MeshHandler::Set(*m4);
        DI::ShaderHandler::Set(*sh4,"res/shaders/spotLight.vert","res/shaders/spotLight.frag");

        // Cube affected to direction point and spot light light
        m5 = C_Ref<DI::Mesh>();
        sh5 = C_Ref<DI::Shader>();
        m5->verticies.count = 396;
        m5->verticies.data = new float[m5->verticies.count]{
                //Pos               //Col                   // Norm                 //Tex
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,      0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
        };
        m5->elements.count = 36;
        m5->elements.data = new unsigned int[m5->elements.count]{
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
        DI::MeshHandler::Set(*m5);
        DI::ShaderHandler::Set(*sh5,"res/shaders/PhongLight_DirPointSpot.vert","res/shaders/PhongLight_DirPointSpot.frag");

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
        
        // Draw geometry with material affected by dir light(Phong)
        DI::ShaderHandler::Use(*sh2);
        DI::ShaderHandler::SetUniform(*sh2, "u_model",m2->model_matrix);
        DI::ShaderHandler::SetUniform(*sh2, "u_proj",view1->proj);
        DI::ShaderHandler::SetUniform(*sh2, "u_view",view1->eye);
        DI::ShaderHandler::SetUniform(*sh2, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::ShaderHandler::SetUniform(*sh2, "viewPos",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh2, "material.shininess",float(0.7 * 128));
        DI::ShaderHandler::SetUniform(*sh2, "light.ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh2, "light.diffuse",0.5f, 0.5f, 0.5f);
        DI::ShaderHandler::SetUniform(*sh2, "light.specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh2, "light.direction",_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);
        DI::RenderHandler::DrawArrays(*m2);

        // Draw geometry with material affected by point light(Phong)
        DI::ShaderHandler::Use(*sh3);
        m3->model_matrix = glm::mat4(1.0f);
        DI::MeshHandler::Translate(*m3,glm::vec3(-10.f,0.0f,0.0f));
        DI::ShaderHandler::SetUniform(*sh3, "u_model",m3->model_matrix);
        DI::ShaderHandler::SetUniform(*sh3, "u_proj",view1->proj);
        DI::ShaderHandler::SetUniform(*sh3, "u_view",view1->eye);
        DI::ShaderHandler::SetUniform(*sh3, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::ShaderHandler::SetUniform(*sh3, "u_color",0.8f,0.22f,0.059f);
        DI::ShaderHandler::SetUniform(*sh3, "viewPos",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh3, "material.shininess",float(0.7 * 128));
        DI::ShaderHandler::SetUniform(*sh3, "light.ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh3, "light.diffuse",0.5f, 0.5f, 0.5f);
        DI::ShaderHandler::SetUniform(*sh3, "light.specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh3, "light.position",_imguiData->slot3, _imguiData->slot4, _imguiData->slot5);
        DI::ShaderHandler::SetUniform(*sh3, "light.constant",1.0f);
        DI::ShaderHandler::SetUniform(*sh3, "light.linear",0.09f);
        DI::ShaderHandler::SetUniform(*sh3, "light.quadratic",0.032f);
        DI::RenderHandler::DrawArrays(*m3);

        // Draw geometry with material affected by spot light(Phong)
        DI::ShaderHandler::Use(*sh4);
        m4->model_matrix = glm::mat4(1.0f);
        DI::MeshHandler::Translate(*m4,glm::vec3(-15.f,-7.0f,0.0f));
        DI::MeshHandler::Scale(*m4,glm::vec3(5.0f,5.0f,5.0f));
        DI::ShaderHandler::SetUniform(*sh4, "u_model",m4->model_matrix);
        DI::ShaderHandler::SetUniform(*sh4, "u_proj",view1->proj);
        DI::ShaderHandler::SetUniform(*sh4, "u_view",view1->eye);
        DI::ShaderHandler::SetUniform(*sh4, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::ShaderHandler::SetUniform(*sh4, "u_color",0.1f,0.84f,0.309f);
        DI::ShaderHandler::SetUniform(*sh4, "viewPos",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh4, "material.shininess",float(0.7 * 128));
        DI::ShaderHandler::SetUniform(*sh4, "light.ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh4, "light.diffuse",0.5f, 0.5f, 0.5f);
        DI::ShaderHandler::SetUniform(*sh4, "light.specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh4, "light.position",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh4, "light.direction",view1->front.x, view1->front.y, view1->front.z);
        DI::ShaderHandler::SetUniform(*sh4, "light.constant",1.0f);
        DI::ShaderHandler::SetUniform(*sh4, "light.linear",0.09f);
        DI::ShaderHandler::SetUniform(*sh4, "light.quadratic",0.032f);
        DI::ShaderHandler::SetUniform(*sh4, "light.cutOff",0.5f);
        DI::ShaderHandler::SetUniform(*sh4, "light.outerCutOff",0.5f);
        DI::RenderHandler::DrawArrays(*m4);
    
        // Draw geometry with material affected by direction, point and spot lighting(Phong)
        DI::ShaderHandler::Use(*sh5);
        m5->model_matrix = glm::mat4(1.0f);
        DI::MeshHandler::Translate(*m5,glm::vec3(0.f,13.0f,0.0f));
        DI::MeshHandler::Scale(*m5,glm::vec3(3.0f,3.0f,3.0f));
        DI::ShaderHandler::SetUniform(*sh5, "u_model",m5->model_matrix);
        DI::ShaderHandler::SetUniform(*sh5, "u_proj",view1->proj);
        DI::ShaderHandler::SetUniform(*sh5, "u_view",view1->eye);
        DI::ShaderHandler::SetUniform(*sh5, "u_time",(float)DI::CoreTime::time_since_start_programm);
        DI::ShaderHandler::SetUniform(*sh5, "u_color",0.4f,0.34f,0.709f);
        DI::ShaderHandler::SetUniform(*sh5, "viewPos",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh5, "material.shininess",float(0.7 * 128));
        DI::ShaderHandler::SetUniform(*sh5, "dirLight.ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh5, "dirLight.diffuse",0.5f, 0.5f, 0.5f);
        DI::ShaderHandler::SetUniform(*sh5, "dirLight.specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh5, "dirLight.direction",_imguiData->slot0, _imguiData->slot1, _imguiData->slot2);

        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].position",_imguiData->slot3, _imguiData->slot4, _imguiData->slot5);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].constant",1.0f);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].linear",0.09f);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].quadratic",0.032f);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].diffuse",0.2f, 0.7f, 0.0f);
        DI::ShaderHandler::SetUniform(*sh5, "pointLights[0].specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.ambient",0.3f, 0.3f, 0.3f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.diffuse",0.5f, 0.5f, 0.5f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.specular",1.0f, 1.0f, 1.0f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.position",view1->pos.x,view1->pos.y,view1->pos.z);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.direction",view1->front.x, view1->front.y, view1->front.z);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.constant",1.0f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.linear",0.09f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.quadratic",0.032f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.cutOff",0.5f);
        DI::ShaderHandler::SetUniform(*sh5, "spotLight.outerCutOff",0.4f);
        DI::RenderHandler::DrawArrays(*m5);
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
    Ref<DI::Mesh>       m2;
    Ref<DI::Mesh>       m3;
    Ref<DI::Mesh>       m4;
    Ref<DI::Mesh>       m5;
    Ref<DI::Shader>     sh1;
    Ref<DI::Shader>     sh2;
    Ref<DI::Shader>     sh3;
    Ref<DI::Shader>     sh4;
    Ref<DI::Shader>     sh5;
    Ref<DI::View>       view1;
    Ref<DI::Texture>    tx3;
};
/*Define our application for mem alloc on engine side*/
DI::App* DI::CreateApp(){
    return new Sandbox();
}