#include "TLC_5947.h"
#include <wiringPi.h>
#include <chrono>
#include <thread>

TLC_5947::TLC_5947(uint16_t n, uint8_t c, uint8_t d,
                                   uint8_t l) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;

  pwmbuffer = (uint16_t *)malloc(2 * 24 * n);
  memset(pwmbuffer, 0, 2 * 24 * n);
}

/*!
 *    @brief  Writes PWM data to the all connected TLC5947 boards
 */

int loopDelay = 2;
void TLC_5947::write() {
  digitalWrite(_lat, LOW);
  // 24 channels per TLC5974
  for (int16_t c = 24 * numdrivers - 1; c >= 0; c--) {
    // 12 bits per channel, send MSB first
    for (int8_t b = 11; b >= 0; b--) {
      for (int i = 0; i < loopDelay; i++){}
      digitalWrite(_clk, LOW);
      for (int i = 0; i < loopDelay; i++){}
      digitalWrite(_dat, pwmbuffer[c] & (1 << b) ? HIGH : LOW);
      for (int i = 0; i < loopDelay; i++){}
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_lat, HIGH);
}

/*!
 *    @brief  Set the PWM channel / value
 *    @param  chan
 *            channel number ([0 - 23] on each board, so chanel 2 for second
 * board will be 25)
 *    @param  pwm
 *            pwm value [0-4095]
 */
void TLC_5947::setPWM(uint16_t chan, uint16_t pwm) {
  /*if (pwm > 4095)
    pwm = 4095;
  if (chan > 24 * numdrivers)
    return; */
  pwmbuffer[chan] = pwm;
}

/*!
 *    @brief  Set LED
 *    @param  lednum
 *            led number
 *    @param  r
 *            red value [0-255]
 *    @param  g
 *            green value [0-255]
 *    @param  b
 *            blue value [0-255]
 */
void TLC_5947::setLED(uint16_t lednum, uint16_t r, uint16_t g,
                              uint16_t b) {
  setPWM(lednum * 3, b);
  setPWM(lednum * 3 + 1, g);
  setPWM(lednum * 3 + 2, r);
}

/*!
 *    @brief  Setups the HW
 *    @return True if initialization was successful, otherwise false.
 */
bool TLC_5947::begin() {
  if (!pwmbuffer)
    return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  return true;
}
