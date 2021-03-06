#pragma once

#include <chrono>

namespace DI{

class CoreTime{
public: 
   CoreTime();
   ~CoreTime();
public:
   static float time_since_start_programm;
   static float tic;
private:
   std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> start;
   std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> end;
};

}