#pragma once

#include <chrono>


class CoreTime{
public: 
   CoreTime();
   ~CoreTime();
public:
   static double time_since_start_programm;
   static double tic;
private:
   std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> start;
   std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> end;
};
