/* File foo.  */
#ifndef CUBE_H
#define CUBE_H

#include "Adafruit_TLC5947.h"
#include <iostream>
#include <unistd.h>
#include <math.h>


// How many boards do you have chained?
#define NUM_TLC5947 8
#define DATA    12
#define CLOCK   14
#define LATCH   21
#define OE     -1  // set to -1 to not use the enable pin (its optional)

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
  float distance(Point b){
    return abs(sqrt((float)pow(b.x - this->x, 2) + (float)pow(b.y - this->y, 2) + (float)pow(b.z - this->z, 2)));
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
  Vector3D(Point start, Point end){
    this->x = end.x - start.x;
    this->y = end.y - start.y;
    this->z = end.z - start.z;
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

enum Plane {
  plane_x,
  plane_y,
  plane_z
};

class Cube {
public:
  Cube();

  void drawLine(Point start, Point end, int r, int g, int b);
 
  void fill(int r, int g, int b);

  void drawCircle(Point *center, int radius, Plane plane);
  
  void drawPixel(Point p, int r, int g, int b);
  
  void handle_draw_frame();
  
  //               x  y  z  rgb
  int frame_buffer[8][8][8][ 3 ] = {0};
private:
  Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5947, CLOCK, DATA, LATCH);
  int layerPins[8] = {1, 0, 2, 3, 4, 5, 6, 22};
  int curLayer = 0;
};

#endif /* !FILE_FOO_SEEN */
