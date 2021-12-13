#include "View.hpp"
#include "Core.hpp"

namespace DI{

void ViewHandler::SetDefault(View &view, glm::vec2 &size){
   view.pos     = glm::vec3(0.0f,0.0f,5.0f);
   view.front   = glm::vec3(0.5f,0.0f,-1.0f);
   view.up      = glm::vec3(0.0f,1.0f,0.0f);
   view.type    = Projection::PERSPECTIVE;
   view.spead   = 30.0f;
   view.fovy    = 45.0f;
   view.yaw     = 0;
   view.pitch   = 0;
   view.ratio   = size.x/size.y;
   view.lastX   = 0;
   view.lastY   = 0;
   view.isFirstTime = true;

   view.eye = glm::mat4(1.0f);
   view.eye = glm::translate(view.eye,glm::vec3(0.0,0.0,-3.0));
   
   view.proj = glm::mat4(1.0f);
   view.proj = glm::perspective(glm::radians(view.fovy),view.ratio,0.1f,10000.0f);
}
void ViewHandler::SetCustom(View &view, const glm::vec3 pos, const glm::vec3 focus, const float spead, const float fovy, const glm::vec2 &size, const Projection type){
   view.pos     = pos;
   view.front   = focus;
   view.up      = glm::vec3(0.0f,1.0f,0.0f);
   view.type    = type;
   view.spead   = spead;
   view.fovy    = fovy;
   view.yaw     = 0;
   view.pitch   = 0;
   view.ratio   = size.x/size.y;
   view.lastX   = 0;
   view.lastY   = 0;
   view.isFirstTime = true;

   view.eye = glm::mat4(1.0f);
   view.eye = glm::translate(view.eye,glm::vec3(0.0,0.0,-3.0));
   
   switch(view.type){
   case Projection::PERSPECTIVE: {  
      view.proj = glm::mat4(1.0f);
      view.proj = glm::perspective(glm::radians(view.fovy),view.ratio,0.1f,100.0f);
      break;
   }
   case Projection::ORTHOGRAPHIC: {
      view.proj = glm::mat4(1.0f);
      view.proj = glm::ortho(0.0f,size.x,0.0f,size.y,0.1f,100.0f);
      break;
   }
   }
}



void ViewHandler::Use(View &view){
   view.eye = glm::lookAt(view.pos,view.pos + view.front,view.up);
}
void ViewHandler::SetPos(View &view, glm::vec3 pos){
   view.pos = pos;
}
void ViewHandler::SetRot(View &view, float angle, glm::vec3 offset){
   // Implement rolling for camera
   glm::vec3 dir;
   DI_LOG_TRACE("roll angle = {0}",view.roll);
   view.roll += angle;
   dir.x = sin(glm::radians(view.roll));
   dir.y = cos(glm::radians(view.roll));
   DI_LOG_TRACE("x = {0}",dir.x);
   DI_LOG_TRACE("y = {0}",dir.y);
   glm::vec3 cam_direc = glm::normalize(view.pos - view.front);
   glm::vec3 cam_right = glm::normalize(glm::cross(dir, cam_direc));
   view.up = glm::cross(cam_direc,cam_right);
}
void ViewHandler::SetMotion(View &view, glm::vec2 motion){
   if (view.isFirstTime){
       view.lastX = motion.x;
       view.lastY = motion.y;
       view.yaw = -90;
       view.isFirstTime = false;
   }
   else{
       float offsetx = motion.x - view.lastX;
       float offsety = view.lastY - motion.y;
       view.lastX = motion.x;
       view.lastY = motion.y;
       const float sensitivity = 0.5f;
       offsetx *= sensitivity;
       offsety *= sensitivity;
       view.yaw += offsetx;
       view.pitch += offsety;
       if(view.pitch > 89.0f)
         view.pitch =  89.0f;
       if(view.pitch < -89.0f)
         view.pitch = -89.0f;
       glm::vec3 direction;
       direction.x = cos(glm::radians(view.yaw)) * cos(glm::radians(view.pitch));
       direction.y = sin(glm::radians(view.pitch));
       direction.z = sin(glm::radians(view.yaw)) * cos(glm::radians(view.pitch));
       view.front = glm::normalize(direction);
   }
}
void ViewHandler::SetZoom(View &view, float motion){
   view.fovy -= motion;
   switch(view.type){
   case Projection::PERSPECTIVE:{   
      view.proj = glm::perspective(glm::radians(view.fovy),view.ratio,0.1f,100.0f);
      break;
   }
   }
}

}
