#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>

#define LEDS_SINGLE_STRIP_PIN 6
#define LEDS_MAIN_STRIP_PIN 5
#define LEDS_MAIN_STRIP_NUM_LEDS 15
#define LEDS_MAIN_STRIP_TOGGLE_OFFSET 5

class LEDs {
  public:
    void setup();
    void updateSingleLED(uint8_t colorH, uint8_t colorS, uint8_t colorV);
    void updateStripLED(uint8_t index, uint8_t colorH, uint8_t colorS, uint8_t colorV);
    void turnOffStripLED(uint8_t index);
    boolean isStripLEDOn(uint8_t index);
    void scrollStripToLeft();
    void scrollStripToRight();
    void off();
    void show();
    void saveStateToEEPROM();
    void loadStateFromEEPROM();
    void loadStateFromEEPROMAndDim(uint8_t dimAmount);
    CRGB mainStrip[LEDS_MAIN_STRIP_NUM_LEDS];
    CRGB singleStrip[1];
  private:
    uint8_t currentIndex;
    static const uint16_t EEPROM_START_OFFSET = 0;
};

#endif
