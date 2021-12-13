#pragma once

#include "DI.hpp"

class MyScene : public DI::Scene{
public:
   MyScene();
   ~MyScene();
   void RenderScene();
   void KeyPressed(int key, bool isKey_repeat);
   void MouseScrolled(glm::vec2 offset);
   void MouseMoved(glm::vec2 pos);
private:
   bool isMouseActive = true;
   Ref<DI::Shader>     sh1;
   Ref<DI::Shader>     sol_shader;
   Ref<DI::Model>      mars;
   Ref<DI::Model>      earth;
   Ref<DI::Model>      moon;
   Ref<DI::Model>      sol;
   Ref<DI::Model>      jupiter;
   Ref<DI::Model>      europe;
   Ref<DI::Model>      kalisto;
   Ref<DI::Model>      io;
   Ref<DI::View>       view1;
};
