#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LEDs {
  public:
    LEDs(uint8_t singleStripPin, uint8_t mainStripPin, uint8_t mainStripNumLEDs);
    void init();
    void updateSingleLED(uint8_t colorR, uint8_t colorG, uint8_t colorB);

  private:
    Adafruit_NeoPixel mainStrip, singleStrip;
    uint8_t numLEDs, currentIndex;
};

#endif
