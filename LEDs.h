#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>

#define SINGLE_STRIP_PIN 6
#define MAIN_STRIP_PIN 5
#define MAIN_STRIP_NUM_LEDS 24
#define MAIN_STRIP_TOGGLE_OFFSET 5

class LEDs {
  public:
    void setup();
    boolean updateSingleLED(uint8_t colorH, uint8_t colorS, uint8_t colorV);
    void toggleStripLED(uint8_t index, uint8_t colorH, uint8_t colorS, uint8_t colorV);
    void scrollStripToLeft();
    void scrollStripToRight();
  private:
    CRGB mainStrip[MAIN_STRIP_NUM_LEDS];
    CRGB singleStrip[1];
    uint8_t currentIndex;
};

#endif
