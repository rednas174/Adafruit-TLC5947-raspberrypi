/* File foo.  */
#ifndef CUBE_H
#define CUBE_H

#include "TLC_5947.h"
#include <iostream>
#include <unistd.h>
#include <math.h>


// How many boards do you have chained?
#define NUM_TLC5947 8
#define DATA    12
#define CLOCK   14
#define LATCH   21
#define OE     -1  // set to -1 to not use the enable pin (its optional)

/* Used for XYZ coordinates */
class Point {
public:
  int x;
  int y;
  int z;
  Point(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
  float distance(Point *b){
    /* Apparently C++17 has an std::hypot(x, y, z), but I guess the C++ used with the RPI does not... */
    return hypot(hypot(b->x - this->x, b->y - this->y), b->z - this->z);
  }
};


class Vector3D {
public:
  float x;
  float y;
  float z;
  Vector3D(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vector3D(Point *start, Point *end){
    this->x = end->x - start->x;
    this->y = end->y - start->y;
    this->z = end->z - start->z;
  }
  void normalize(float scaling){
    float magnitude = abs(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
    this->x = (this->x / magnitude) * scaling;
    this->y = (this->y / magnitude) * scaling;
    this->z = (this->z / magnitude) * scaling;
  }
  void normalize(){
    this->normalize(1);
  }
};

/*
enum Plane {
  plane_x,
  plane_y,
  plane_z
};
*/

class Cube {
public:
  Cube();

  void drawLine(Point *start, Point *end, int r, int g, int b);
 
  void fill(int r, int g, int b);

  void drawSphere(Point *center, int radius, int r, int g, int b, bool mode_additive);
  void drawSphere(Point *center, int radius, int r, int g, int b);
  
  void drawCube(Point *A, Point *B, int r, int g, int b);
  
  void drawPixel(Point *p, int r, int g, int b);
  
  bool capCube(Point *A, Point *B);
  
  void handle_draw_frame();
  
  /* 4D frame buffer x  y  z  rgb */
  int   frame_buffer[8][8][8][ 3 ] = {0};
private:
  TLC_5947 tlc = TLC_5947(NUM_TLC5947, CLOCK, DATA, LATCH);

  /* DON'T TOUCH THESE!!! (pins for the LEDcube) */
  int layerPins[8] = {1, 0, 2, 3, 4, 5, 6, 22};
  int curLayer = 0;
};

#endif /* !FILE_FOO_SEEN */
