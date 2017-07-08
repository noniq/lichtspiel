#include <Arduino.h>
#include "LEDs.h"

void LEDs::setup() {
  FastLED.addLeds<WS2812, SINGLE_STRIP_PIN, RGB>(singleStrip, 1);
  FastLED.addLeds<NEOPIXEL, MAIN_STRIP_PIN>(mainStrip, MAIN_STRIP_NUM_LEDS);
  currentIndex = 0;
}

void LEDs::updateSingleLED(uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  singleStrip[0].setHSV(colorH, colorS, colorV);
  FastLED.show();
}

void LEDs::updateStripLED(uint8_t index, uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  uint8_t stripIndex = MAIN_STRIP_TOGGLE_OFFSET + index;
  mainStrip[stripIndex].setHSV(colorH, colorS, colorV);
  FastLED.show();
}

void LEDs::turnOffStripLED(uint8_t index) {
  uint8_t stripIndex = MAIN_STRIP_TOGGLE_OFFSET + index;
  mainStrip[stripIndex] = 0;
  FastLED.show();
}

void LEDs::scrollStripToLeft() {
  CRGB first = mainStrip[0];
  for (uint8_t i = 0; i < MAIN_STRIP_NUM_LEDS - 1; i++) {
    mainStrip[i] = mainStrip[i + 1];
  }
  mainStrip[MAIN_STRIP_NUM_LEDS - 1] = first;
}

void LEDs::scrollStripToRight() {
  CRGB last = mainStrip[MAIN_STRIP_NUM_LEDS - 1];
  for (uint8_t i = MAIN_STRIP_NUM_LEDS - 1; i > 0; i--) {
    mainStrip[i] = mainStrip[i - 1];
  }
  mainStrip[0] = last;
}

void LEDs::off() {
  singleStrip[0] = 0;
  for (uint8_t i = 0; i < MAIN_STRIP_NUM_LEDS; i++) {
    mainStrip[i] = 0;
  }
  FastLED.show();
}
