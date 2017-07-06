#include <Arduino.h>
#include "Pulser.h"

Pulser::Pulser(uint8_t _pin) {
  pin = _pin;
  counter = 0;
  value = 255;
  direction = -1;
}

void Pulser::pulse() {
  counter++;
  if (counter == 5) {
    counter = 0;
    value += direction;
    if (value == 280 || value == 128) direction = -direction;
    if (value < 256) analogWrite(pin, value);
  }
}
