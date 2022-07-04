#include "Time.hpp"
#include <iostream>

namespace DI{

float CoreTime::time_since_start_programm = 0;
float CoreTime::tic = 0;

CoreTime::CoreTime(){
   start = std::chrono::steady_clock::now();
}

CoreTime::~CoreTime(){
   end = std::chrono::steady_clock::now();
   std::chrono::duration<float> elapsed_seconds = end - start;
   tic = elapsed_seconds.count();
   time_since_start_programm += elapsed_seconds.count();
}

}