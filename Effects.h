#ifndef EFFECTS_H
#define EFFECTS_H

#include "LEDs.h"
#include "Rotary.h"

class Effects {
  public:
    void setup(LEDs *_leds);
    void doEffect(uint8_t effect, Rotary::Action action);
    void noEffect();

  private:
    void scroll(uint32_t ms, Rotary::Action action);
    void knightRider(uint32_t ms);
    void blink(boolean firstTime, Rotary::Action action);
    void makeRainbow(boolean firstTime, uint32_t ms, Rotary::Action action);
    void colorChase(uint32_t ms, Rotary::Action action);

    LEDs *leds;
    uint32_t lastUpdate = 0;
    uint8_t lastEffect = 0;
};

#endif
