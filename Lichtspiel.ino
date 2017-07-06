#include <avr/sleep.h>
#include <EEPROM.h>

#include "InteractionTimeout.h"
#include "LEDs.h"
#include "Rotary.h"
#include "Pulser.h"

#ifdef DEV
static const uint16_t INTERACTION_TIMEOUT_SECONDS = 10;
#else
static const uint16_t INTERACTION_TIMEOUT_SECONDS = 120;
#endif
static const uint16_t EEPROM_HALT_AFTER_RESET = 0;
static const uint8_t NUM_BUTTONS = 5;
static const uint8_t BUTTON_PINS[NUM_BUTTONS] = {9, 13, 10, 12, 11};
static const uint8_t ANALOG_H_IN_PIN = 1;
static const uint8_t ANALOG_S_IN_PIN = 0;
static const uint8_t ANALOG_V_IN_PIN = 2;
static const uint8_t ROTARY_PIN_A = 2;
static const uint8_t ROTARY_PIN_B = 4;
static const uint8_t ROTARY_PORT = PIND;
static const uint8_t RESET_SWITCH_LED_PIN = 3;

uint8_t lastButtonState[NUM_BUTTONS] = {HIGH};
uint8_t mapS[256];
uint8_t mapV[256];

InteractionTimeout interactionTimeout(INTERACTION_TIMEOUT_SECONDS);
Rotary rotary(ROTARY_PIN_A, ROTARY_PIN_B, ROTARY_PORT);
Rotary::Action action;
LEDs leds;
Pulser resetSwitchPulser(RESET_SWITCH_LED_PIN);

void handleHaltAfterReset() {
  uint8_t haltAfterReset = EEPROM.read(EEPROM_HALT_AFTER_RESET);
  EEPROM.write(EEPROM_HALT_AFTER_RESET, 1 - haltAfterReset);
  if (haltAfterReset) sleep_mode();
}

void setup() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  handleHaltAfterReset();

  leds.setup();
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
  resetSwitchPulser.pulse();

  uint8_t h = analogRead(ANALOG_H_IN_PIN) >> 2;
  uint8_t s = mapS[analogRead(ANALOG_S_IN_PIN) >> 2];
  uint8_t v = mapV[analogRead(ANALOG_V_IN_PIN) >> 2];
  if (leds.updateSingleLED(h, s, v)) interactionTimeout.reset();

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (buttonPressed(i)) {
      leds.toggleStripLED(i, h, s, v);
      interactionTimeout.reset();
    }
  }

  action = rotary.read();
  switch (action) {
    case Rotary::LEFT:
      leds.scrollStripToLeft();
      interactionTimeout.reset();
      break;
    case Rotary::RIGHT:
      leds.scrollStripToRight();
      interactionTimeout.reset();
      break;
    default:
      break;
  }

  if (interactionTimeout.timedOut()) sleep_mode();
}
