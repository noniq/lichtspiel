#include "Lichtspiel.h"
#include "LEDs.h"
#include "Rotary.h"

static const uint8_t NUM_BUTTONS = 5;
static const uint8_t BUTTON_PINS[NUM_BUTTONS] = {9, 13, 10, 12, 11};

uint8_t lastButtonState[NUM_BUTTONS] = {HIGH};
uint8_t mapS[256];
uint8_t mapV[256];

Rotary rotary;
Rotary::Action action;
LEDs leds;

void setup() {
  leds.init();
  rotary.setup();
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  for (uint16_t i = 0; i < 256; i++) {
    mapS[i] = 64 + (256 - 64) / 256.0 * i;
    mapV[i] = i / 2 + 48;
  }
}

bool buttonPressed(uint8_t index) {
  uint8_t state = digitalRead(BUTTON_PINS[index]);
  if (state == LOW && lastButtonState[index] == HIGH) {
    lastButtonState[index] = LOW;
    return true;
  };
  lastButtonState[index] = state;
  return false;
}

void loop() {
  uint8_t h = analogRead(ANALOG_H_IN_PIN) >> 2;
  uint8_t s = mapS[analogRead(ANALOG_S_IN_PIN) >> 2];
  uint8_t v = mapV[analogRead(ANALOG_V_IN_PIN) >> 2];

  leds.updateSingleLED(h, s, v);

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (buttonPressed(i)) leds.toggleStripLED(i, h, s, v);
  }

  action = rotary.read();
  switch (action) {
    case Rotary::LEFT:
      leds.scrollStripToLeft();
      break;
    case Rotary::RIGHT:
      leds.scrollStripToRight();
      break;
    default:
      break;
  }
}
