#include "Cube.h"


Cube::Cube(){

  std::cout << "starting...\n";

  /* Start WiringPi for I2C and pin definitions */
  wiringPiSetup();
  
  /* Setup MOSFETs and set to off */
  for (int i = 0; i <= 8; i++){
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }

  /* setup relay to power LED cube */
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  /* Write first layer to ON */
  digitalWrite(layerPins[0], HIGH);

  /* start PWM drivers */
  tlc.begin();

  /* If Output Enabled pin is define, set to low so output is always enabled*/
  if (OE >= 0) {
    pinMode(OE, OUTPUT);
    digitalWrite(OE, LOW);
  }
  std::cout << "Started successfully\n";
}

void Cube::drawLine(Point *start, Point *end, int r, int g, int b){
  float step_size = 0.5;
  float x = (float)start->x;
  float y = (float)start->y;
  float z = (float)start->z;
  float distance = (float)Point((int)x, (int)y, (int)z).distance(end);

  /* Algorithm used:
   * Idk what it's called, but it steps through the cube from start to end (in step_size steps)
   * It then picks the closest LED for each step and sets that to the given RGB value 
  */
  for (int i = 0; i < distance / step_size; i++){
    drawPixel(new Point(round(x), round(y), round(z)), r, g, b);
    Vector3D vector = Vector3D(start, end);
    vector.normalize(step_size);
    x += (vector.x);
    y += (vector.y);
    z += (vector.z);
  }
}

/* Function overloading for if no mode_additive is needed */
void Cube::drawSphere(Point *center, int radius, int r, int g, int b){
  this->drawSphere(center, radius, r, g, b, false);
}

/* Algorithm used:
 * For all LEDs in the cube, check if their distance is less or equal to the given radius
 * 
 * TODO: Since radius is defined, check only the LEDs within a cube of that radius
*/
void Cube::drawSphere(Point *center, int radius, int r, int g, int b, bool mode_additive){
  
  Point *min = new Point(center->x - radius, center->y - radius, center->z - radius);
  Point *max = new Point(center->x + radius+1, center->y + radius+1, center->z + radius+1);
  if (this->capCube(min, max)){
  //for(int x = 0; x < 8; x++){
  //  for(int y = 0; y < 8; y++){
  //    for(int z = 0; z < 8; z++){
   for(int x = min->x; x < max->x; x++){
     for(int y = min->y; y < max->y; y++){
       for(int z = min->z; z < max->z; z++){
         if (center->distance(new Point(x,y,z)) <= radius){
           if (mode_additive){
             frame_buffer[x][y][z][0] += r;
             frame_buffer[x][y][z][1] += g;
             frame_buffer[x][y][z][2] += b;
           }
           else{
             frame_buffer[x][y][z][0] = r;
             frame_buffer[x][y][z][1] = g;
             frame_buffer[x][y][z][2] = b;
            }
          }
        }
      }
    }
  }
}

/* Returns: boolean that indicates if the cube has a subarea within the LED cube.
 *
*/ 
bool Cube::capCube(Point *A, Point *B){
  /*if((A->x > 7 || A->y > 7 || A->z > 7 ||
      A->x < 0 || A->y < 0 || A->z < 0) &&
     (B->x > 7 || B->y > 7 || B->z > 7 ||
      B->x < 0 || B->y < 0 || B->z < 0))
    */
  int x_start = (A->x > B->x ? B->x : A->x); // get the smallest X value
  int x_end   = (A->x > B->x ? A->x : B->x); // get the biggest X value
  int y_start = (A->y > B->y ? B->y : A->y); // get the smallest Y value
  int y_end   = (A->y > B->y ? A->y : B->y); // get the biggest Z value
  int z_start = (A->z > B->z ? B->z : A->z); // get the smallest Y value
  int z_end   = (A->z > B->z ? A->z : B->z); // get the biggest Z value
  
  int amount_changed = 0;
  
  if (x_start < 0){
    x_start = 0;
    amount_changed++;
  }
  if (x_end   > 8){
    x_end   = 8;
    amount_changed++;
  }
  
  if (y_start < 0){
    y_start = 0;
    amount_changed++;
  }
  
  if (y_end   > 8){
    y_end   = 8;
    amount_changed++;
  }
  
  if (z_start < 0){
    z_start = 0;
    amount_changed++;
  }
  
  if (z_end   > 8){
    z_end   = 8;
    amount_changed++;
  }

  A->x = x_start;
  A->y = y_start;
  A->z = z_start;
  B->x = x_end;
  B->y = y_end;
  B->z = z_end;

  if(amount_changed >= 6) return false;
  else return true;
}
/* Algorithm used:
 * Extract lowest/highest XYZ, then make everything within those 2 points a colour.
*/
void Cube::drawCube(Point *A, Point *B, int r, int g, int b){
  int x_start = (A->x > B->x ? B->x : A->x); // get the smallest X value
  int x_end   = (A->x > B->x ? A->x : B->x); // get the biggest X value
  int y_start = (A->y > B->y ? B->y : A->y); // get the smallest Y value
  int y_end   = (A->y > B->y ? A->y : B->y); // get the biggest Z value
  int z_start = (A->z > B->z ? B->z : A->z); // get the smallest Y value
  int z_end   = (A->z > B->z ? A->z : B->z); // get the biggest Z value

  for (int x = x_start; x < x_end; x++){
    for (int y = y_start; y < y_end; y++){
      for (int z = z_start; z < z_end; z++){
        frame_buffer[x][y][z][0] = r;
        frame_buffer[x][y][z][1] = g;
        frame_buffer[x][y][z][2] = b;
      }
    }
  }

}

/* No algorithm used */
void Cube::drawPixel(Point *p, int r, int g, int b){
  frame_buffer[(int)p->x][(int)p->y][(int)p->z][0] = r;
  frame_buffer[(int)p->x][(int)p->y][(int)p->z][1] = g;
  frame_buffer[(int)p->x][(int)p->y][(int)p->z][2] = b;
}


/* For entire cube, fill with colour */
void Cube::fill(int r, int g, int b){
  for (int x = 0; x < 8; x++){
    for (int y = 0; y < 8; y++){
      for (int z = 0; z < 8; z++){    
        frame_buffer[x][y][z][0] = r;
        frame_buffer[x][y][z][1] = g;
        frame_buffer[x][y][z][2] = b;
      }
    }
  }
}

void Cube::handle_draw_frame(){
  /* Go to next layer */
  digitalWrite(layerPins[curLayer], LOW);
  curLayer = (curLayer + 1) % 8;
  
  /* Write the layer pixels */
  for (int x = 0; x < 8; x++){
    for (int z = 0; z < 8; z++){
      tlc.setLED(x + z * 8, frame_buffer[x][curLayer][z][0], frame_buffer[x][curLayer][z][1], frame_buffer[x][curLayer][z][2]);
    }
  }
  /* Write to the TLC drivers */
  tlc.write();
  digitalWrite(layerPins[curLayer], HIGH);
}
