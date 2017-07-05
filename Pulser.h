#ifndef PULSER_H
#define PULSER_H

#include "Arduino.h"

#define PULSER_PWM_PIN 3

class Pulser {
  public:
    void init();
    void pulse();
  private:
    uint16_t counter, value;
    int8_t direction;
};

#endif
