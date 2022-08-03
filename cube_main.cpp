#include "Cube.h"
#include <signal.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <pthread.h>


/*     +-----------------+
 *     | o o o o o o o o |
 *     | o o o o o o o o |
 *     | o o o o o o o o |
 * ====+ o o o o o o o o |
 *     | o o o o o o o o |
 *     | o o o o o o o o |
 *   ^ | o o o o o o o o |
 *   | | o o o o o o o o |
 *   Z +-----------------+
 *   
 *   Y  X-->
*/




Cube cube = Cube();

void interrupt_routine(int call_num);
void *display_frames(void *vargp);

void draw_moving_dot();
void draw_blocks();
void draw_circles();
void draw_white(int intensity);
void draw_colour(int r, int g, int b);
void draw_23();
void wait();

int usdelay_LED_1024    = 395 * 2;
int usdelay/*_visual*/  = 395 * 5;
int usdelay_camera      = 800;
pthread_t thread_id;

int in = 4095;

int main(){
  
  /* Wait for system to fully have booted */
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  
  /* START necessary code for starting thread */
  pthread_create(&thread_id, NULL, display_frames, NULL);
  /* END */
  
  /* Uncomment for individual functions */
  // moving_dot();
  // draw_blocks();
  // draw_circles();
  // draw_colour(4095, 0, 0);
  // draw_white(2048);
  
  while (1){
    for (int i = 0; i < 4; i++)
      draw_23();
    draw_moving_dot();
    draw_blocks();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int i = 0; i < 4; i++)
      draw_circles();
  }
  return 1;
}

void wait(){
  while (true){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
void draw_23(){
  int r_2 = 0;
  int g_2 = 0;
  int b_2 = 4095;
  
  int r_3 = 0;
  int g_3 = 4095;
  int b_3 = 0;
  
  for (int z = 0; z < 8; z++){
    // Draw the 2
    cube.drawPixel(new Point(0,5,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(0,6,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(1,7,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(2,7,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(3,6,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(3,5,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(3,4,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(2,3,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(1,2,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(0,1,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(0,0,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(1,0,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(2,0,z), r_2, g_2, b_2);
    cube.drawPixel(new Point(3,0,z), r_2, g_2, b_2);
    
    // Draw the 3
    cube.drawPixel(new Point(4,6,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(5,7,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(6,7,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(7,6,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(7,5,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(6,4,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(5,4,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(7,3,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(7,2,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(7,1,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(6,0,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(5,0,z), r_3, g_3, b_3);
    cube.drawPixel(new Point(4,1,z), r_3, g_3, b_3);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    cube.fill(0,0,0);
  }
}

void draw_white(int intensity){
  cube.fill(intensity, intensity, intensity);
}

void draw_colour(int r, int g, int b){
  cube.fill(r, g, b);
}

void draw_circles(){
  cube.drawSphere(new Point(4, 4, 4),     2, 0,    0,    4095, true);
  for (int i = -2; i < 10; i++){
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    cube.fill(0,0,0);
    cube.drawSphere(new Point(i,7-i,i),     2, 4095, 0,    0,    true);
    cube.drawSphere(new Point(7-i,7-i,7-i), 3, 0,    4095, 0,    true);
    cube.drawSphere(new Point(4, 4, 4),     2, 0,    0,    4095, true);
  }
}

void draw_blocks(){
  cube.drawCube(new Point(0,0,0), new Point(4,4,4), 0   , 0   , 0   );
  cube.drawCube(new Point(0,0,4), new Point(4,4,8), 0   , 0   , 4095);
  cube.drawCube(new Point(0,4,0), new Point(4,8,4), 0   , 4095, 0   );
  cube.drawCube(new Point(0,4,4), new Point(4,8,8), 0   , 4095, 4095);
  cube.drawCube(new Point(4,0,0), new Point(8,4,4), 4095, 0   , 0   );
  cube.drawCube(new Point(4,0,4), new Point(8,4,8), 4095, 0   , 4095);
  cube.drawCube(new Point(4,4,0), new Point(8,8,4), 4095, 4095, 0   );
  cube.drawCube(new Point(4,4,4), new Point(8,8,8), 4095, 4095, 4095);
  cube.drawLine(new Point(0,0,0), new Point(8,8,7), 256 , 2048 , 256);
}

void draw_moving_dot(){
  cube.fill(128, 128, 128);
  Point *prevP = new Point(0,0,0); 
  Point *newP  = new Point(0,0,0);
  for (int x = 0; x < 8; x++){
    for (int y = 0; y < 8; y++){
      for (int z = 0; z < 8; z++){
        newP = new Point(x,y,z);
        cube.drawPixel(prevP, 0,0,0);
        cube.drawPixel(newP, 4095, 4095, 4095);
        prevP = newP;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
    }
  }
}

void *display_frames(void *vargp){
  while (true){
    cube.handle_draw_frame();
    std::this_thread::sleep_for(std::chrono::microseconds(usdelay));
  }
}

void interrupt_routine(int call_num){
  if (call_num == SIGINT){
    pthread_exit(&thread_id);
  }
}
