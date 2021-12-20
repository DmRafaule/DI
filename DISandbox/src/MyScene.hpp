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
   Ref<DI::View>       view1;
};
