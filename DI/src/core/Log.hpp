#pragma once 

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "memory"

namespace DI{

class Log{
public: 
   static void Init();
   inline static std::shared_ptr<spdlog::logger>& getConsoleEngine() { return _ConsoleEngine; };
   inline static std::shared_ptr<spdlog::logger>& getConsoleClient() { return _ConsoleClient; };
private:
   static std::shared_ptr<spdlog::logger> _ConsoleEngine;
   static std::shared_ptr<spdlog::logger> _ConsoleClient;
};


};

// Macros for Engine side login system
#define DI_LOG_TRACE(...) ::DI::Log::getConsoleEngine()->trace(__VA_ARGS__)
#define DI_LOG_INFO(...)  ::DI::Log::getConsoleEngine()->info(__VA_ARGS__)
#define DI_LOG_WARN(...)  ::DI::Log::getConsoleEngine()->warn(__VA_ARGS__)
#define DI_LOG_ERROR(...) ::DI::Log::getConsoleEngine()->error (__VA_ARGS__)
#define DI_LOG_DEBUG(...) ::DI::Log::getConsoleEngine()->debug (__VA_ARGS__)
// Macros for App side login system
#define APP_LOG_TRACE(...) ::DI::Log::getConsoleClient()->trace(__VA_ARGS__)
#define APP_LOG_INFO(...)  ::DI::Log::getConsoleClient()->info(__VA_ARGS__)
#define APP_LOG_WARN(...)  ::DI::Log::getConsoleClient()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::DI::Log::getConsoleClient()->error (__VA_ARGS__)
#define APP_LOG_DEBUG(...)  ::DI::Log::getConsoleClient()->debug (__VA_ARGS__)