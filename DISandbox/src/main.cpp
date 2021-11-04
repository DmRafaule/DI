
#include "Debuger.hpp"
#include "Time.hpp"
#include <cstdio>


int main (int argc, char **argv){
    
    printf("%f\n",CoreTime::time_since_start_programm);
    CoreTime a;
    a.OUT();
    a.IN();
    return 0;
}