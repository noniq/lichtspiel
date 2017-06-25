#include "Arduino.h"
#include "LEDs.h"

void LEDs::init() {
  FastLED.addLeds<WS2812, SINGLE_STRIP_PIN, RGB>(singleStrip, 1);
  FastLED.addLeds<WS2812B, MAIN_STRIP_PIN, GRB>(mainStrip, MAIN_STRIP_NUM_LEDS);
  currentIndex = 0;
}

void LEDs::updateSingleLED(uint8_t colorR, uint8_t colorG, uint8_t colorB) {
  singleStrip[0].r = colorR;
  singleStrip[0].g = colorG;
  singleStrip[0].b = colorB;

  mainStrip[currentIndex] = 0;
  currentIndex++;
  if (currentIndex >= MAIN_STRIP_NUM_LEDS) currentIndex = 0;
  mainStrip[currentIndex].r = colorR;
  mainStrip[currentIndex].g = colorG;
  mainStrip[currentIndex].b = colorB;

  FastLED.show();
}

