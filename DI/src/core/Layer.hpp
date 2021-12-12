#pragma once 

#include "Core.hpp"

namespace DI{
   
   class Scene;

   struct Layer{
      std::string name; // Name for layer
      int index;        // Whis position for rendering
      std::function<void()> callback; // What kind of function to call
   };

   class LayerHandler{
   friend class SceneHandler;
   public:
      // Set new layer
      static void Set(std::string l_name, const int index, std::function<void()> func, std::vector<Layer>& layers);
      // Unset(remove) layer
      static void UnSet(std::string l_name, std::vector<Layer>& layers);
      // Unset(remove) all layers
      static void Clear(std::vector<Layer>& layers);
   private:
      // Update all layer data
      static void Update(std::vector<Layer>& layers);
      LayerHandler();
   };

} // namespace DI
