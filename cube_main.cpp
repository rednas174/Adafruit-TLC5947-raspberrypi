#include "Cube.h"

#include <signal.h>
#include <chrono>
#include <thread>

Cube cube = Cube();

void interrupt_routine(int call_num);

int usdelay = 10 * 1000;  

int main(){

  // signal(SIGALRM, interrupt_routine);   
  // ualarm(1, usdelay);
  
  // for (int i = 0; i < 4; i++)
  // cube.drawPixel(Point(0,i,0), 100, 100, 100);
  /*
  cube.drawLine(Point(0,0,0), Point(7,7,7));
  cube.drawLine(Point(0,0,7), Point(7,7,0));
  cube.drawLine(Point(7,0,0), Point(0,7,7));
  cube.drawLine(Point(0,7,0), Point(7,0,7));
  */
  // cube.drawLine(Point(0,7,6), Point(7,0,0));
  cube.drawLine(Point(7,0,0), Point(0,7,4));

  while(true){
    interrupt_routine(SIGALRM);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  return 1;
}


void interrupt_routine(int call_num){
  if (call_num == SIGALRM){
    cube.handle_draw_frame();
  }
}
