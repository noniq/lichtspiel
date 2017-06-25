#include "Arduino.h"
#include "Lichtspiel.h"
#include "LEDs.h"

LEDs::LEDs(uint8_t singleStripPin, uint8_t mainStripPin, uint8_t mainStripNumLEDs) {
  numLEDs = mainStripNumLEDs;
  singleStrip = Adafruit_NeoPixel(1, singleStripPin, NEO_RGB + NEO_KHZ800);
  mainStrip = Adafruit_NeoPixel(mainStripNumLEDs, mainStripPin, NEO_GRB + NEO_KHZ800);
  currentIndex = 0;
}

void LEDs::init() {
  singleStrip.begin();
  mainStrip.begin();
}

void LEDs::updateSingleLED(uint8_t colorR, uint8_t colorG, uint8_t colorB) {
  singleStrip.setPixelColor(0, colorR, colorG, colorB);
  singleStrip.show();

  mainStrip.setPixelColor(currentIndex, 55, 55, 55);
  currentIndex++;
  if (currentIndex >= numLEDs) currentIndex = 0;
  mainStrip.setPixelColor(currentIndex, colorR, colorG, colorB);
  mainStrip.show();
}

