#pragma once 

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/fmt/ostr.h"
#include "glm/vec4.hpp"
#include <memory>
#include <vector>
#include <string>

namespace DI{

class GUIHandler;

struct LogData{
   std::vector<std::pair<std::string,glm::vec4>> buffer;
};

class Log{
public: 
   static void Init();
   inline static std::shared_ptr<spdlog::logger>& getConsoleEngine() { return _ConsoleEngine; };
   inline static std::shared_ptr<spdlog::logger>& getConsoleClient() { return _ConsoleClient; };
   static std::shared_ptr<LogData>        _logData;
private:
   static std::shared_ptr<spdlog::logger> _ConsoleEngine;
   static std::shared_ptr<spdlog::logger> _ConsoleClient;
};


};
// HERE add logs in editor
// Macros for Engine side login system
#define DI_LOG_TRACE(...) ::DI::Log::getConsoleEngine()->trace(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0)))

#define DI_LOG_INFO(...)  ::DI::Log::getConsoleEngine()->info(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(0.0,1.0,0.0,1.0)))

#define DI_LOG_WARN(...)  ::DI::Log::getConsoleEngine()->warn(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0,1.0,0.0,1.0)))

#define DI_LOG_ERROR(...) ::DI::Log::getConsoleEngine()->error (__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0,0.0,0.0,1.0)))

#define DI_LOG_DEBUG(...) ::DI::Log::getConsoleEngine()->debug (__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(0.0,0.0,1.0,1.0)))

                     
// Macros for App side login system
#define APP_LOG_TRACE(...) ::DI::Log::getConsoleClient()->trace(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0)))

#define APP_LOG_INFO(...)  ::DI::Log::getConsoleClient()->info(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(0.0,1.0,0.0,1.0)))

#define APP_LOG_WARN(...)  ::DI::Log::getConsoleClient()->warn(__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0,1.0,0.0,1.0)))

#define APP_LOG_ERROR(...) ::DI::Log::getConsoleClient()->error (__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(1.0,0.0,0.0,1.0)))

#define APP_LOG_DEBUG(...)  ::DI::Log::getConsoleClient()->debug (__VA_ARGS__);\
                          ::DI::Log::_logData->buffer.push_back(std::pair<std::string,glm::vec4>(fmt::v8::format(__VA_ARGS__),glm::vec4(0.0,0.0,1.0,1.0)))

