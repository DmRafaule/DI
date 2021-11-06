#pragma once

#include "Core.hpp"


namespace DI{
/*
* Kinds of supported events
*/
enum class EventType{
   None,
   AppUpdate, AppRender, AppTick,
   WinClose, WinResize, WinFocus,WinMoved,
   KeyPressed, KeyReleased,
   MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};
/*
* 'Where' events came from 
*/
enum EventSource{
   NONE,
   APP,
   KEYBOARD,
   MOUSE,
   WIN,
};
/*
* Macroses for avoiding copypasting the same code, and I'm lazy 
*/
#define EVENT_TYPE( type ) static EventType getStaticType( ) { return EventType::type; } \
                           virtual  EventType getEventType() const override { return getStaticType(); }\
                           virtual  const char* getName() const override { return #type; }\

#define EVENT_SOURCE(source)  virtual int getSourceFlags() const override { return source; }\

/*
* Base class for all events
*/
class Event{
   friend class EventDispatcher;
public:
   virtual int getSourceFlags() const = 0;
   virtual const char* getName() const = 0; //Maybe not needed
   virtual EventType getEventType() const = 0;
   // For informing logging system about what happends
   virtual std::string toStr() const { return getName(); }; 
   // Is this event belongs to 'src' 
   inline bool isFromSource( EventSource src){ return getSourceFlags() & src; };
protected:
   bool _handled = false;
};

/*
*
*/
class EventDispatcher{
   template<typename T>
   using EventFn = std::function<bool(T&)>;
public:
   EventDispatcher(Event& event) : _event(event){}
   template<typename T>
   bool dispatch(EventFn<T> func){
      if (_event.getEventType() == T::getStaticType()){
         _event._handled = func(*(T*)&_event);
         return true;
      }
      return false;
   }
private:
   Event& _event;
};

/*
* Overloading << operator for usin in *_LOG_* macros in Log.hpp
*/
inline std::ostream& operator<<(std::ostream& os, const Event& e){
   return os << e.toStr();
}

};