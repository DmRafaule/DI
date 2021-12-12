#pragma once

#include "Core.hpp"
#include <SDL_events.h>


namespace DI{
   enum EventType : unsigned int{
        WIN_CLOSED,
        WIN_RESIZED,
        WIN_MOVED,
        WIN_FOCUS,
        WIN_MINIMIZED,
        APP_FRAME,
        KEY_PRESSED,
        KEY_RELEASED,
        MOUSE_MOVED,
        MOUSE_PRESSED,
        MOUSE_RELEASED,
        MOUSE_SCROLLED,
        CUSTOM_EVENT,
   };

   struct Event{
        std::string name;
        EventType   type;
        std::function<void()> callback;
   };
   class EventsHandler{
   friend class App;
   public:
     static void Set(EventType type,std::function<void()> func){
          switch(type){
               case EventType::WIN_MINIMIZED:{
                    WinMinimized = func;
                    break;
               }
               case EventType::WIN_FOCUS:{
                    WinFocused   = func;
                    break;
               }
               case EventType::WIN_CLOSED:{
                    WinClosed    = func;
                    break;
               }
               case EventType::APP_FRAME:{
                    AppFrameChanged = func;
                    break;
               }
          }
     };
     static void Set(EventType type, std::function<void(int)> func){
          switch(type){
               case EventType::KEY_RELEASED:{
                    KeyReleased = func;
                    break;
               }
               case EventType::MOUSE_RELEASED:{
                    MouseReleased    = func;
                    break;
               }
          }
     }
     static void Set(EventType type, std::function<void(int,bool)> func){
          switch(type){
               case EventType::KEY_PRESSED:{
                    KeyPressed = func;
                    break;
               }
               case EventType::MOUSE_PRESSED:{
                    MousePressed   = func;
                    break;
               }
          }
     }
     static void Set(EventType type, std::function<void(glm::vec2)> func){
          switch(type){
               case EventType::WIN_RESIZED:{
                    WinResized   = func;
                    break;
               }
               case EventType::WIN_MOVED:{
                    WinMoved     = func;
                    break;
               } 
               case EventType::MOUSE_MOVED:{
                    MouseMoved   = func;
                    break;
               }
               case EventType::MOUSE_SCROLLED:{
                    MouseScrolled    = func;
                    break;
               }
          }
     }
     static void Set(EventType type, std::function<void(SDL_Event&)> func){
          CustomEvent = func;
     }
   private:
     static std::function<void()>            WinMinimized;
     static std::function<void(glm::vec2)>   WinResized;
     static std::function<void(glm::vec2)>   WinMoved;
     static std::function<void()>            WinFocused;
     static std::function<void()>            WinClosed;
     static std::function<void(int,bool)>    KeyPressed;
     static std::function<void(int)>         KeyReleased;
     static std::function<void()>            AppFrameChanged;
     static std::function<void(glm::vec2)>   MouseMoved;
     static std::function<void(glm::vec2)>   MouseScrolled;
     static std::function<void(int,bool)>    MousePressed;
     static std::function<void(int)>         MouseReleased;
     static std::function<void(SDL_Event&)>  CustomEvent;
     static Event event;
     EventsHandler();
   };

}
