#ifndef EFFECTS_H
#define EFFECTS_H

#include "LEDs.h"
#include "Rotary.h"

class Effects {
  public:
    void setup(LEDs *_leds);
    void doEffect(uint8_t effect, Rotary::Action action);

  private:
    void scroll(uint16_t ms, Rotary::Action action);
    void knightRider(uint16_t ms);

    LEDs *leds;
    uint32_t lastUpdate = 0;
  };

#endif
