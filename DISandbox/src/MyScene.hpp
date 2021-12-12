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
   Ref<DI::Shader>     sh2;
   Ref<DI::Shader>     sh3;
   Ref<DI::Shader>     sh4;
   Ref<DI::Model>      model1;
   Ref<DI::Model>      model2;
   Ref<DI::Model>      model3;
   Ref<DI::Model>      model4;
   Ref<DI::View>       view1;
};
