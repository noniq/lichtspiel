#include <Arduino.h>

#include "EffectPlugs.h"

EffectPlugs::EffectPlugs(uint8_t _num, const uint8_t *_pins) {
  num = _num;
  pins = _pins;
}

void EffectPlugs::setup() {
  for (uint8_t i = 0; i < num; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
}

uint8_t EffectPlugs::pluggedConnection() {
  uint8_t connection = 0, foundConnection = 0;
  for (uint8_t i = 0; i < num; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
    for (uint8_t j = i + 1; j < num; j++) {
      connection++;
      if (digitalRead(pins[j]) == LOW) foundConnection = connection;
    }
    pinMode(pins[i], INPUT_PULLUP);
  }
  return foundConnection;
}
