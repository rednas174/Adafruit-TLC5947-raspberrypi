#ifndef _TLC_5947_H
#define _TLC_5947_H

#include <wiringPi.h>
#include <stdlib.h>
#include <cstring>
#include <stdint.h>
#include <iostream>

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            TLC5947 24-channel PWM/LED driver
 */
class TLC_5947 {
public:
  TLC_5947(uint16_t n, uint8_t c, uint8_t d, uint8_t l);

  bool begin(void);

  void setPWM(uint16_t chan, uint16_t pwm);
  void setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b);
  void write();

private:
  uint16_t *pwmbuffer;

  uint16_t numdrivers;
  uint8_t _clk, _dat, _lat;
};

#endif
