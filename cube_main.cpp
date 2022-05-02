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

  cube.drawPixel(Point(0,0,0), 1024, 0, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cube.drawPixel(Point(7,0,0), 0, 1024, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cube.drawPixel(Point(7,7,0), 0, 0, 1024);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cube.drawPixel(Point(7,7,7), 1024, 1024, 1024);
  std::this_thread::sleep_for(std::chrono::milliseconds(25000000));


  while(true){
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    for (int i = 0; i < 8; i++){
      cube.fill(0,0,0);
      cube.drawLine(Point(7,0,0), Point(0,7-i,7), 1024, 1024, 1024);
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    for (int i = 0; i < 8; i++){
      cube.fill(0,0,0);
      cube.drawLine(Point(7,i,0), Point(0,7-i,7), 1024, 1024, 1024);
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
  }
  return 1;
}


void interrupt_routine(int call_num){
  if (call_num == SIGALRM){
    cube.handle_draw_frame();
  }
}
