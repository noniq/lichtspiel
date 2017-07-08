#include <Arduino.h>

#include "Effects.h"


void Effects::setup(LEDs *_leds) {
  leds = _leds;
}

void Effects::doEffect(uint8_t effect, Rotary::Action action) {
  uint32_t ms = millis() - lastUpdate;

  switch (effect) {
    case 1:
      scroll(ms, action);
      break;
    case 2:
      knightRider(ms);
      break;
    default:
      break;
  }
}

void Effects::scroll(uint16_t ms, Rotary::Action action) {
  static constexpr int8_t MAX_SCROLL_SPEED = 8;
  static constexpr uint16_t SCROLL_SPEED_TO_MS[8] = {
    500, 400, 300, 200, 150, 100, 66, 33
  };
  static int8_t scrollSpeed = 2;

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

void Effects::knightRider(uint16_t ms) {
  static constexpr uint8_t DELAY = 50;
  static int8_t position = 0;
  static uint8_t direction = 1;

  for (int8_t i = 0; i < LEDS_MAIN_STRIP_NUM_LEDS; i++) {
    if      (i == position)                 leds->mainStrip[i].setHSV(0, 250, 200);
    else if (i == position - direction)     leds->mainStrip[i].setHSV(0, 250, 100);
    else if (i == position - direction * 2) leds->mainStrip[i].setHSV(0, 250, 75);
    else if (i == position - direction * 3) leds->mainStrip[i].setHSV(0, 250, 50);
    else if (i == position - direction * 4) leds->mainStrip[i].setHSV(0, 250, 25);
    else leds->mainStrip[i] = 0;
  }
  leds->show();
  if (ms > DELAY) {
    position += direction;
    if (position >= LEDS_MAIN_STRIP_NUM_LEDS) {
      direction = -direction;
    } else if (position < 0) {
      direction = -direction;
    }
    lastUpdate = millis();
  }
}
