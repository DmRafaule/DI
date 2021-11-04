#include "Time.hpp"
#include <iostream>

double CoreTime::time_since_start_programm = 0;
double CoreTime::tic = 0;

CoreTime::CoreTime(){
   start = std::chrono::steady_clock::now();
}

CoreTime::~CoreTime(){
   end = std::chrono::steady_clock::now();
   std::chrono::duration<double> elapsed_seconds = end - start;
   tic = elapsed_seconds.count();
   time_since_start_programm += elapsed_seconds.count();
}