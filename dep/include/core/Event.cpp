#include "Event.hpp"


namespace DI{

std::function<void()>            EventsHandler::WinMinimized        = []()->void{};
std::function<void(glm::vec2)>   EventsHandler::WinResized          = [](glm::vec2 vec)->void{};
std::function<void(glm::vec2)>   EventsHandler::WinMoved            = [](glm::vec2 vec)->void{};
std::function<void()>            EventsHandler::WinFocused          = []()->void{};
std::function<void()>            EventsHandler::WinClosed           = []()->void{};
std::function<void(int,bool)>    EventsHandler::KeyPressed          = [](int a,bool b)->void{};
std::function<void(int)>         EventsHandler::KeyReleased         = [](int a)->void{};
std::function<void()>            EventsHandler::AppFrameChanged     = []()->void{};
std::function<void(glm::vec2)>   EventsHandler::MouseMoved          = [](glm::vec2 vec)->void{};
std::function<void(glm::vec2)>   EventsHandler::MouseScrolled       = [](glm::vec2 vec)->void{};
std::function<void(int,bool)>    EventsHandler::MousePressed        = [](int a,bool b)->void{};
std::function<void(int)>         EventsHandler::MouseReleased       = [](int a)->void{};
std::function<void(SDL_Event&)>  EventsHandler::CustomEvent         = [](SDL_Event& e)->void{};;    

Event EventsHandler::event;

}
