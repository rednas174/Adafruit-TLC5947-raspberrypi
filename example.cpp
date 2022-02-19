/*************************************************** 
  This is an example for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  Ported to wiringPi by rednas174

  BSD license, all text above must be included in any redistribution
 ****************************************************/




#include "Adafruit_TLC5947.h"
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <chrono>
#include <thread>

// How many boards do you have chained?
#define NUM_TLC5947 4

#define data    12
#define clock   14
#define latch   21
#define oe     -1  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5947, clock, data, latch);

void loop();
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait);
void rainbowCycle(uint8_t wait);
void Wheel(uint8_t ledn, uint16_t WheelPos);
void make_red();
void make_green();
void make_blue();
void interrupt_routine(int call_num);


int pin = 30;

int usdelay = 500 * 1000;

int main() {
 
  std::cout << "starting...\n";

  wiringPiSetup();	
  tlc.begin();

  signal(SIGALRM, interrupt_routine);   
  ualarm(1, usdelay);

  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }

  std::cout << "Started successfully, timer interrupt handles the switching of the colours :)\n";

  while (1){
  	std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 1;

}

int v = 0;
int inc = 100;
int max = 2048;
void make_red(){
  v+=inc;
  v = v%max;
  for (int i = 0; i < 8 * NUM_TLC5947; i++){
    tlc.setLED(i, v, 0, 0);
  }
  tlc.write();
}

void make_green(){
  v+=inc;
  v = v%max;
  for (int i = 0; i < 8 * NUM_TLC5947; i++){
    tlc.setLED(i, 0, v, 0);
  }
  tlc.write();
}

void make_blue(){
  v+=inc;
  v = v%max;
  for (int i = 0; i < 8 * NUM_TLC5947; i++){
    tlc.setLED(i, 0, 0, v);
  }
  tlc.write();
}


int cur_val = 0;

void interrupt_routine(int call_num){
  if (call_num == SIGALRM){
    cur_val = (cur_val + 1) % 3;
    switch(cur_val){
      case 0:
	make_red();
	break;
      case 1:
	make_green();
	break;
      case 2:
	make_blue();
	break;
      default:
	break;
    }

  }

}

// Input a value 0 to 4095 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel(uint8_t ledn, uint16_t WheelPos) {
  if(WheelPos < 1365) {
    tlc.setLED(ledn, 3*WheelPos, 4095 - 3*WheelPos, 0);
  } else if(WheelPos < 2731) {
    WheelPos -= 1365;
    tlc.setLED(ledn, 4095 - 3*WheelPos, 0, 3*WheelPos);
  } else {
    WheelPos -= 2731;
    tlc.setLED(ledn, 0, 3*WheelPos, 4095 - 3*WheelPos);
  }
}
