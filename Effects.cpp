#include <Arduino.h>

#include "Effects.h"

const uint16_t Effects::SCROLL_SPEED_TO_MS[8] = {
  500, 400, 300, 200, 150, 100, 66, 33
};

void Effects::setup(LEDs *_leds) {
  leds = _leds;
}

void Effects::doEffect(uint8_t effect, Rotary::Action action) {
  uint32_t ms = millis() - lastUpdate;

  switch (effect) {
    case 1:
      scroll(ms, action);
      break;

    default:
      break;
  }
}

void Effects::scroll(uint16_t ms, Rotary::Action action) {
  if (ms > SCROLL_SPEED_TO_MS[abs(scrollSpeed)]) {
    if (scrollSpeed > 0) leds->scrollStripToRight(); else leds->scrollStripToLeft();
    lastUpdate = millis();
  }
  switch (action) {
    case Rotary::LEFT:
      if (scrollSpeed > -MAX_SCROLL_SPEED + 1) scrollSpeed--;
      break;
    case Rotary::RIGHT:
      if (scrollSpeed < MAX_SCROLL_SPEED - 1) scrollSpeed++;
      break;
    default:
      break;
  }
}
