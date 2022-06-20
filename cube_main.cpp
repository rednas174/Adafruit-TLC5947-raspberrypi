#include "Cube.h"

#include <signal.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>

Cube cube = Cube();

void interrupt_routine(int call_num);

// useconds  / (  4MHz  / steps)
// 1.000.000 / (4194304 / 4095) ~= 976.3 usec / cycle
// int usdelay = 2929;
int usdelay = 1250;
int usdelay_OLD = 2500;

int main(){

  signal(SIGALRM, interrupt_routine);   
  ualarm(1, usdelay);

  srand(time(0));

  std::this_thread::sleep_for(std::chrono::milliseconds(25));

  int r = 0;
  int g = 0;
  int b = 0;
  int sleep = 100;
  while(true){
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    
    for (int layer = 0; layer < 8; layer++){
      switch(layer % 2){
        case 0:
          for (int i = 0; i < 8; i++){
            if (i == 0){
              r = rand()%1024;
              g = rand()%1024;
              b = rand()%1024;
	    }
	    cube.fill(0,0,0);
            cube.drawLine(Point(0,layer,i), Point(7,layer,7-i), r, g, b);
	    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	  }
          
          break;
        case 1:
          for (int i = 0; i < 8; i++){
	    cube.fill(0,0,0);
            cube.drawLine(Point(7-i,layer,0), Point(i,layer,7), r, g, b);
	    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	  }
          break;
      }
    }
  }
  return 1;
}


void interrupt_routine(int call_num){
  if (call_num == SIGALRM){
    cube.handle_draw_frame();
  }
}
