#pragma once 

#include "Core.hpp"
#include "Layer.hpp"

namespace DI{

   class Scene {
   public:
      Scene();
      virtual ~Scene();
      virtual void Use(){};
      std::vector<Layer> layers;
   };

   class SceneHandler{
   friend class App;
   public:
      static void Set(const std::string name, Scene& scene);
      static void UnSet(const std::string name);
      static void Change(const std::string name);
      static void Clear();
   private:
      static std::unordered_map<std::string,Scene> scenes;
      static Scene* currentScene;
      static void Update();
      SceneHandler();
   };

} // namespace DI
