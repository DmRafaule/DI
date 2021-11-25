#pragma once 

#include <glm/gtc/type_ptr.hpp>

namespace DI{

enum Projection{
   PERSPECTIVE,
   ORTHOGRAPHIC,
};

struct View{
   Projection type;// Type of Projection matrix
   glm::mat4 eye;  // View matrix
   glm::mat4 proj; // Projection matrix
   
   glm::vec3 pos;  // View position
   glm::vec3 front;// View focus
   glm::vec3 up;   // View up axis
   float spead;    // Spead of tranlation matrix to all vertecies
   
   float fovy;     // Angle of vision for view
   
   float yaw;     
   float pitch;
   float roll;
   float ratio;    // Ratio of screen 

   // Find other place
   float lastX, lastY;
   bool isFirstTime;
};

// Create overloaded func for  diff types of cammeras
class ViewHandler{
public:
   
   static void SetDefault(View &view, glm::vec2 &size);
   static void SetCustom(View &view,const glm::vec3 pos,const glm::vec3 focus,const float spead,const float fovy,const glm::vec2 &size, const Projection type);
   static void Use(View &view);
   static void SetPos(View &view, glm::vec3 pos);
   static void SetRot(View &view, float angle, glm::vec3 offset);
   static void SetMotion(View &view, glm::vec2 motion);
   static void SetZoom(View &view, float motion);

private:
};

}