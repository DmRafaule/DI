#include "Scene.hpp"


namespace DI{

extern Scope<DebugData> _debugData;

Scene::Scene(){
   DI_LOG_TRACE("SceneHandler say: init scene");
}
Scene::~Scene(){
   DI_LOG_TRACE("SceneHandler say: remove scene");
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
   _debugData->counterDICalls = 0;
   _debugData->counterDIElements_inUse = 0;
   _debugData->counterDIVerticies_inUse = 0;
   _debugData->counterDIMeshes_inUse = 0;
   _debugData->counterDIModels_inUse = 0;
   _debugData->counterDITextures_inUse = 0;
   if (currentScene != nullptr)
      LayerHandler::Update(currentScene->layers);
}


}
