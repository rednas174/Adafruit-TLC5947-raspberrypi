#include "Cube.h"


Cube::Cube(){

  std::cout << "starting...\n";
  wiringPiSetup();
  
  for (int i = 0; i <= 8; i++){
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }

  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
  digitalWrite(layerPins[0], HIGH);

  tlc.begin();

  if (OE >= 0) {
    pinMode(OE, OUTPUT);
    digitalWrite(OE, LOW);
  }

  std::cout << "Started successfully, timer interrupt handles the switching of the colours :)\n";
}

void Cube::drawLine(Point start, Point end){
  float step_size = 0.5;
  float x = (float)start.x;
  float y = (float)start.y;
  float z = (float)start.z;
  while (Point((int)x, (int)y, (int)z).distance(end) > 1){
    printf("%f, %f, %f\n", x, y, z);
    drawPixel(Point(round(x), round(y), round(z)), 0, 100, 255);
    Vector3D vector = Vector3D(start, end);
    vector.normalize();
    x += (vector.x * step_size);
    y += (vector.y * step_size);
    z += (vector.z * step_size);
  } 
  drawPixel(Point(round(x), round(y), round(z)), 0, 100, 255);
}

void Cube::drawCircle(Point *center, int radius, Plane plane){

}
  
void Cube::drawPixel(Point p, int r, int g, int b){
  frame_buffer[p.x][p.y][p.z][0] = r;
  frame_buffer[p.x][p.y][p.z][1] = g;
  frame_buffer[p.x][p.y][p.z][2] = b;
}

void Cube::handle_draw_frame(){
  // Go to next layer
  digitalWrite(layerPins[curLayer], LOW);
  // curLayer = 5;
  curLayer = (curLayer + 1) % 8;
  // Write the layer pixels
  for (int x = 0; x < 8; x++){
    for (int z = 0; z < 8; z++){
      tlc.setLED(x + z * 8, frame_buffer[x][curLayer][z][0], frame_buffer[x][curLayer][z][1], frame_buffer[x][curLayer][z][2]);
    }
  }
  tlc.write();
  digitalWrite(layerPins[curLayer], HIGH);
}

float distance(Point a, Point b){
  return abs(sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}
