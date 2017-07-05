#include "Arduino.h"
#include "Pulser.h"

void Pulser::init() {
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
    if (value < 256) analogWrite(PULSER_PWM_PIN, value);
  }
}
