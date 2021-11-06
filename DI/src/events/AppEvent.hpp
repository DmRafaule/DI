#pragma once 

#include "Event.hpp"

namespace DI{

class AppTick : public Event{
public:
	AppTick() = default;
	EVENT_TYPE(AppTick);
	EVENT_SOURCE(EventSource::APP);
};

class AppUpdate : public Event{
public:
	AppUpdate() = default;
	EVENT_TYPE(AppUpdate);
	EVENT_SOURCE(EventSource::APP);
};

class AppRender : public Event{
public:
	AppRender() = default;
	EVENT_TYPE(AppRender);
	EVENT_SOURCE(EventSource::APP);
};
} // namespace DI
