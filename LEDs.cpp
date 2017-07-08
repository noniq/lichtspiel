#include <Arduino.h>
#include <EEPROM.h>
#include "LEDs.h"

void LEDs::setup() {
  FastLED.addLeds<WS2812, LEDS_SINGLE_STRIP_PIN, RGB>(singleStrip, 1);
  FastLED.addLeds<NEOPIXEL, LEDS_MAIN_STRIP_PIN>(mainStrip, LEDS_MAIN_STRIP_NUM_LEDS);
  currentIndex = 0;
}

void LEDs::updateSingleLED(uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  singleStrip[0].setHSV(colorH, colorS, colorV);
  FastLED.show();
}

void LEDs::updateStripLED(uint8_t index, uint8_t colorH, uint8_t colorS, uint8_t colorV) {
  uint8_t stripIndex = LEDS_MAIN_STRIP_TOGGLE_OFFSET + index;
  mainStrip[stripIndex].setHSV(colorH, colorS, colorV);
  FastLED.show();
}

void LEDs::turnOffStripLED(uint8_t index) {
  uint8_t stripIndex = LEDS_MAIN_STRIP_TOGGLE_OFFSET + index;
  mainStrip[stripIndex] = 0;
  FastLED.show();
}

boolean LEDs::isStripLEDOn(uint8_t index) {
  uint8_t stripIndex = LEDS_MAIN_STRIP_TOGGLE_OFFSET + index;
  return mainStrip[stripIndex].r != 0 || mainStrip[stripIndex].g != 0 || mainStrip[stripIndex].b != 0;
}

void LEDs::scrollStripToLeft() {
  CRGB first = mainStrip[0];
  for (uint8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS - 1; i++) {
    mainStrip[i] = mainStrip[i + 1];
  }
  mainStrip[LEDS_MAIN_STRIP_NUM_LEDS - 1] = first;
}

void LEDs::scrollStripToRight() {
  CRGB last = mainStrip[LEDS_MAIN_STRIP_NUM_LEDS - 1];
  for (uint8_t i = LEDS_MAIN_STRIP_NUM_LEDS - 1; i > 0; i--) {
    mainStrip[i] = mainStrip[i - 1];
  }
  mainStrip[0] = last;
}

void LEDs::off() {
  singleStrip[0] = 0;
  for (uint8_t j = 0; j < 10; j++) {
    for (uint8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS; i++) {
      mainStrip[i].fadeToBlackBy(64);
    }
    singleStrip[0].fadeToBlackBy(64);
    FastLED.show();
    delay(30);
  }
  for (uint8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS; i++) {
    mainStrip[i] = 0;
  }
  FastLED.show();
}

void LEDs::saveStateToEEPROM() {
  for (uint8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS; i++) {
    EEPROM.update(EEPROM_START_OFFSET + i * 3 + 0, mainStrip[i].r);
    EEPROM.update(EEPROM_START_OFFSET + i * 3 + 1, mainStrip[i].g);
    EEPROM.update(EEPROM_START_OFFSET + i * 3 + 2, mainStrip[i].b);
  }
}

void LEDs::loadStateFromEEPROM() {
  for (uint8_t j = 0; j < 10; j++) {
    for (uint8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS; i++) {
      mainStrip[i].r = EEPROM.read(EEPROM_START_OFFSET + i * 3 + 0);
      mainStrip[i].g = EEPROM.read(EEPROM_START_OFFSET + i * 3 + 1);
      mainStrip[i].b = EEPROM.read(EEPROM_START_OFFSET + i * 3 + 2);
      for (uint8_t k = 9; k > j; k--) {
        mainStrip[i].fadeToBlackBy(64);
      }
    }
    FastLED.show();
    delay(30);
  }
}
