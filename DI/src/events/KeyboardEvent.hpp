#pragma once

#include "Event.hpp"

namespace DI{

class Key : public Event{
public:
   inline int getKeyCode() const { return _keyCode; };
   EVENT_SOURCE(EventSource::KEYBOARD);
protected:
   Key(int keycode) : _keyCode(keycode) {}
   int _keyCode;
};

class KeyPressed : public Key {
public:
   KeyPressed(int keyCode, int repeatCount) : Key(keyCode), _repeatCount(repeatCount) {}
   inline int getRepeatCount() const  { return _repeatCount; };
   std::string toStr() const override{
      std::stringstream ss;
      ss << "KeyPressed event: " << _keyCode << "(" << _repeatCount << ") repeats" ;
      return ss.str();
   }
   EVENT_TYPE(KeyPressed);
protected:
   int _repeatCount;
};

class KeyReleased : public Key{
public: 
   KeyReleased(int keyCode) : Key(keyCode) {}
   std::string toStr() const override {
      std::stringstream ss;
      ss << "KeyReleased event: " << _keyCode;
      return ss.str();
   }
   EVENT_TYPE(KeyReleased);
};


};