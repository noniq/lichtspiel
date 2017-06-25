#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"
#include "FastLED.h"

#define SINGLE_STRIP_PIN 6
#define MAIN_STRIP_PIN 5
#define MAIN_STRIP_NUM_LEDS 24
#define MAIN_STRIP_TOGGLE_OFFSET 10

class LEDs {
  public:
    void init();
    void updateSingleLED(uint8_t colorR, uint8_t colorG, uint8_t colorB);
    void toggleStripLED(uint8_t index, uint8_t colorR, uint8_t colorG, uint8_t colorB);
    void scrollStripToLeft();
    void scrollStripToRight();
  private:
    CRGB mainStrip[MAIN_STRIP_NUM_LEDS];
    CRGB singleStrip[1];
    uint8_t currentIndex;
};

#endif
