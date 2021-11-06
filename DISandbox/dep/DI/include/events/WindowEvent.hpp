#include "Event.hpp"

namespace DI{

class WinResize : public Event{
public:
	WinResize(glm::vec2 size)
		: _size(size) {}
	inline glm::vec2 getSize() const { return _size; };
	std::string toStr() const override{
		std::stringstream ss;
		ss << "WindowResize event : " << _size.x << ", " << _size.y;
      return ss.str();
	}
   EVENT_TYPE(WinResize);
   EVENT_SOURCE(EventSource::WIN);
private:
	glm::vec2 _size;
};

class WinClose : public Event{
public:
	WinClose() = default;
	EVENT_TYPE(WinClose);
	EVENT_SOURCE(EventSource::WIN);
};

class WinFocus : public Event{
public:
   WinFocus(bool focus) : _focus(focus) {}
   inline bool isFocused() const { return _focus; };
   std::string toStr() const override{
		std::stringstream ss;
		ss << "WindowFocused event : " << (_focus ? "true" : "false");
      return ss.str();
	}
   EVENT_TYPE(WinFocus);
   EVENT_SOURCE(EventSource::WIN);
private:
   bool _focus;
};

class WinMoved : public Event{
public:
   WinMoved(glm::vec2 pos) : _pos(pos) {}
   inline glm::vec2 getPos() const { return _pos; };
   std::string toStr() const override{
		std::stringstream ss;
		ss << "WindowMoved event : x=" << _pos.x << " y=" << _pos.y;
      return ss.str();
	}

   EVENT_TYPE(WinMoved);
   EVENT_SOURCE(EventSource::WIN);
private:
   glm::vec2 _pos;
};

};