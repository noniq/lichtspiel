#ifndef PULSER_H
#define PULSER_H

#include <Arduino.h>

class Pulser {
  public:
    Pulser(uint8_t _pin);
    void pulse();
    void steady();
    void off();
  private:
    static const uint8_t delay = 30;
    uint8_t pin;
    uint16_t value;
    int8_t direction;
    uint32_t lastUpdate;
};

#endif
