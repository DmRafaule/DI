#include "Scene.hpp"


namespace DI{

Scene::Scene(){
}
Scene::~Scene(){
}


std::unordered_map<std::string,Scene> SceneHandler::scenes;
Scene* SceneHandler::currentScene = nullptr;
void SceneHandler::Set(const std::string name, Scene& scene){
   scenes.emplace(name,scene);
   currentScene = &scene;
}
void SceneHandler::UnSet(const std::string name){
   scenes.erase(name);
}
void SceneHandler::Change(const std::string name){
   auto isExist = scenes.find(name);
   if (isExist != scenes.end()){
      currentScene = &isExist->second;
   }
}
void SceneHandler::Clear(){
   for (auto& s : scenes)
      LayerHandler::Clear(s.second.layers);
   scenes.clear();
}
void SceneHandler::Update(){
   if (currentScene != nullptr)
      LayerHandler::Update(currentScene->layers);
}


}
