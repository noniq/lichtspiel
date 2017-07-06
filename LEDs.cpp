#include <Arduino.h>
#include "LEDs.h"

void LEDs::setup() {
  FastLED.addLeds<WS2812, SINGLE_STRIP_PIN, RGB>(singleStrip, 1);
  FastLED.addLeds<WS2812B, MAIN_STRIP_PIN, GRB>(mainStrip, MAIN_STRIP_NUM_LEDS);
  currentIndex = 0;
}

boolean LEDs::updateSingleLED(uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  static uint8_t lastH, lastS, lastV;
  singleStrip[0].setHSV(colorH, colorS, colorV);
  FastLED.show();
  boolean changed = colorH != lastH || colorS != lastS || colorV || lastV;
  lastH = colorH;
  lastS = colorS;
  lastV = colorV;
  return changed;
}

void LEDs::toggleStripLED(uint8_t index, uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  uint8_t stripIndex = MAIN_STRIP_TOGGLE_OFFSET + index;
  if ((mainStrip[stripIndex].r == 0) && (mainStrip[stripIndex].g == 0) && (mainStrip[stripIndex].b == 0)) {
    mainStrip[stripIndex].setHSV(colorH, colorS, colorV);
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
