#ifndef ROTARY_H
#define ROTARY_H

#include <Arduino.h>

class Rotary {
  public:
    enum Action {
      NONE, LEFT, RIGHT, TIMEOUT
    };

#ifdef DEV
		static const uint32_t TIMEOUT_MILLIS = 20 * 1000UL;
#else
		static const uint32_t TIMEOUT_MILLIS = 120 * 1000UL;
#endif

    Rotary();
    void setup();
    Action read();
    Action waitForAction();

  private:
    uint8_t _prevPos, _flags, pinA, pinB, port;
    uint8_t readEnc();
};

#endif
