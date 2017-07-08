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

    LEDs *leds;
    uint32_t lastUpdate = 0;

    static constexpr int8_t MAX_SCROLL_SPEED = 8;
    static const uint16_t SCROLL_SPEED_TO_MS[8];
    int8_t scrollSpeed = 2;
};

#endif
