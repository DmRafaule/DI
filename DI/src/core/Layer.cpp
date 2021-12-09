#include "Layer.hpp"

namespace DI{
   std::vector<Layer> LayerHandler::layers(0);
   
   void LayerHandler::Set(std::string l_name, const int index,std::function<void()> func){
      Layer l_new;
      l_new.name  = l_name;
      l_new.index = index;
      l_new.callback  = func;
      DI_LOG_INFO("LayerHandler say: Set layer {0} ",l_name);
      layers.push_back(l_new);
      std::sort(layers.begin(),layers.end(),[&](const Layer &layerA, const Layer &layerB){
         return layerB.index > layerA.index;
      });
   }
   void LayerHandler::UnSet(std::string l_name){
      for (int i = 0; i < layers.size(); i++){
         if (layers[i].name.compare(l_name)){
            DI_LOG_INFO("LayerHandler say: UnSet {0}",layers[i].name);
            layers.erase(layers.begin()+i);
         }
      }
   }
   void LayerHandler::Update(){
      for (int i = 0; i < layers.size(); i++){
         layers[i].callback();
      }
   }

} // namespace DI
