#ifndef PULSER_H
#define PULSER_H

#include <Arduino.h>

class Pulser {
  public:
    Pulser(uint8_t _pin);
    void pulse();
  private:
    uint8_t pin;
    uint16_t counter, value;
    int8_t direction;
};

#endif
