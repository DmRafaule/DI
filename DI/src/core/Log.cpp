#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace DI{
   std::shared_ptr<spdlog::logger> Log::_ConsoleEngine;
   std::shared_ptr<spdlog::logger> Log::_ConsoleClient;
   std::shared_ptr<LogData>        Log::_logData;
   void Log::Init(){
      _logData = std::make_shared<LogData>();
      spdlog::set_pattern("%^%n-> %v %$");
      _ConsoleEngine =  spdlog::stdout_color_mt("DI"); 
      _ConsoleEngine->set_level(spdlog::level::trace);

      _ConsoleClient =  spdlog::stdout_color_mt("APP");
      _ConsoleClient->set_level(spdlog::level::trace);

      DI_LOG_TRACE("Init Loggin system");
   }
}