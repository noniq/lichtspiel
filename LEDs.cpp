#include "Arduino.h"
#include "LEDs.h"

void LEDs::init() {
  FastLED.addLeds<WS2812, SINGLE_STRIP_PIN, RGB>(singleStrip, 1);
  FastLED.addLeds<WS2812B, MAIN_STRIP_PIN, GRB>(mainStrip, MAIN_STRIP_NUM_LEDS);
  currentIndex = 0;
}

void LEDs::updateSingleLED(uint8_t colorR, uint8_t colorG, uint8_t colorB) {
  singleStrip[0].setRGB(colorR, colorG, colorB);
  FastLED.show();
}

void LEDs::toggleStripLED(uint8_t index, uint8_t colorR, uint8_t colorG, uint8_t colorB) {
  uint8_t stripIndex = MAIN_STRIP_TOGGLE_OFFSET + index;
  if ((mainStrip[stripIndex].r == 0) && (mainStrip[stripIndex].g == 0) && (mainStrip[stripIndex].b == 0)) {
    mainStrip[stripIndex].setRGB(colorR, colorG, colorB);
  } else {
    mainStrip[stripIndex] = 0;
  }
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
