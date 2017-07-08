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
    case 5:
      knightRider(ms);
      break;
    case 3:
      blink(effect != lastEffect, action);
      break;
    case 2:
      makeRainbow(effect != lastEffect, ms, action);
      break;
    default:
      break;
  }
  lastEffect = effect;
}

void Effects::noEffect() {
  if (lastEffect == 3) {
    leds->loadStateFromEEPROMAndDim(0);
  }
  lastEffect = 0;
}

void Effects::scroll(uint32_t ms, Rotary::Action action) {
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

void Effects::knightRider(uint32_t ms) {
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

void Effects::blink(boolean firstTime, Rotary::Action action) {
  static constexpr uint8_t MAX_BLINK_SPEED = 4;
  static int8_t blinkSpeed = 1;
  static int16_t dimAmount = 0;
  static int8_t direction = 1;
  if (firstTime) leds->saveStateToEEPROM();
  leds->loadStateFromEEPROMAndDim(dimAmount);
  dimAmount += direction * blinkSpeed * 2;
  if (dimAmount > 255) {
    dimAmount = 255;
    direction = -direction;
  } else if (dimAmount < 0) {
    dimAmount = 0;
    direction = -direction;
  }
  switch (action) {
    case Rotary::LEFT:
      if (blinkSpeed > 0 ) blinkSpeed--;
      break;
    case Rotary::RIGHT:
      if (blinkSpeed < MAX_BLINK_SPEED) blinkSpeed++;
      break;
    default:
      break;
  }
}

void Effects::makeRainbow(boolean firstTime, uint32_t ms, Rotary::Action action) {
  static constexpr uint8_t MAX_SPEED = 8;
  static constexpr uint16_t SPEED_TO_MS[8] = {
    500, 400, 300, 200, 150, 100, 66, 33
  };
  static uint8_t speed = 4;
  static int8_t step = 0;
  static boolean phase2 = false;

  if (firstTime) {
    step = 0;
    phase2 = false;
    speed = 4;
  }
  if (ms > SPEED_TO_MS[speed]) {
    lastUpdate = millis();
    if (step < LEDS_MAIN_STRIP_NUM_LEDS) {
      for (uint8_t i = 0; i <= step; i++) {
        if (phase2) {
          leds->mainStrip[i] = 0;
        } else {
          leds->mainStrip[i].setHSV(255.0 / LEDS_MAIN_STRIP_NUM_LEDS * i, 250, 200);
        }
      }
      step++;
    } else {
      phase2 = !phase2;
      step = 0;
    }
  }

  switch (action) {
    case Rotary::LEFT:
      if (speed > 0 ) speed--;
      break;
    case Rotary::RIGHT:
      if (speed < MAX_SPEED - 1) speed++;
      break;
    default:
      break;
  }
}
