#pragma once 

#include "Core.hpp"

namespace DI{
   
   class App;

   struct Layer{
      std::string name;
      int index;
      std::function<void()> callback;
   };

   class LayerHandler{
   friend class App;
   public:
      static void Set(std::string l_name, const int index, std::function<void()> func);
      static void UnSet(std::string l_name);
   private:
      static std::vector<Layer> layers;
      static void Update();
      LayerHandler();
   };

} // namespace DI
