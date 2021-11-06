#pragma once

#include "Event.hpp"

namespace  DI{

/*
*
*/   
class MouseMoved : public Event{
public:
   MouseMoved(glm::vec2 pos) : _pos(pos) {}
   inline glm::vec2 getPos() const { return _pos; };
   std::string toStr() const override{
      std::stringstream ss;
      ss << "MouseMoved event: x=" << _pos.x << " y=" << _pos.y;
      return ss.str();
   }
   EVENT_TYPE(MouseMoved);
   EVENT_SOURCE(EventSource::MOUSE);
private:   
   glm::vec2 _pos;
};

/*
*
*/
class MouseScrolled : public Event{
public:
   MouseScrolled(glm::vec2 offset) : _offset(offset) {}
   inline glm::vec2 getOffset() const { return _offset; };
   std::string toStr() const override{
      std::stringstream ss;
      ss << "MouseScrolled event: x=" << _offset.x << " y=" << _offset.y;
      return ss.str();
   }
   EVENT_TYPE(MouseScrolled);
   EVENT_SOURCE(EventSource::MOUSE);
private:   
   glm::vec2 _offset;
};

/*
*
*/
class MouseButton : public Event{
public:
   inline int getMouseButton() const { return _button; };
   EVENT_SOURCE(EventSource::MOUSE);
protected:   
   MouseButton(int button) : _button(button) {}
   int _button;
};

/*
*
*/
class MouseButtonPressed : public MouseButton{
public:
   MouseButtonPressed(int button) : MouseButton(button) {}
   std::string toStr() const override{
      std::stringstream ss;
      ss << "MouseButtonPressed : " << _button;
      return ss.str();
   }
   EVENT_TYPE(MouseButtonPressed);
};

/*
*
*/
class MouseButtonReleased : public MouseButton{
public:
   MouseButtonReleased(int button) : MouseButton(button) {}
   std::string toStr() const override{
      std::stringstream ss;
      ss << "MouseButtonReleased : " << _button;
      return ss.str();
   }
   EVENT_TYPE(MouseButtonReleased);
};


}; // namespace  DI
