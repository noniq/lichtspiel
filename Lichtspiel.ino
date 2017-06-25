#include "Lichtspiel.h"
#include "LEDs.h"
#include "Rotary.h"

static const uint8_t NUM_BUTTONS = 4;
static const uint8_t BUTTON_PINS[NUM_BUTTONS] = {8, 9, 10, 11};

uint8_t lastButtonState[NUM_BUTTONS] = {HIGH};
uint8_t analogValueToColorMapping[256];

Rotary rotary;
Rotary::Action action;
LEDs leds;

void setup() {
  Serial.begin(115200);
  leds.init();
  rotary.setup();
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  for (uint16_t i = 0; i < 256; i++) {
    analogValueToColorMapping[i] = 2 + (i >> 1); // TODO: better mapping
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
  uint8_t r = analogValueToColorMapping[analogRead(ANALOG_R_IN_PIN) >> 2];
  uint8_t g = analogValueToColorMapping[analogRead(ANALOG_G_IN_PIN) >> 2];
  uint8_t b = analogValueToColorMapping[analogRead(ANALOG_B_IN_PIN) >> 2];
  leds.updateSingleLED(r, g, b);

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (buttonPressed(i)) leds.toggleStripLED(i, r, g, b);
  }

  action = rotary.read();
  Serial.println("action");
  switch (action) {
    case Rotary::LEFT:
      Serial.println("LEFT");
      leds.scrollStripToLeft();
      break;
    case Rotary::RIGHT:
      Serial.println("RIGHT");
      leds.scrollStripToRight();
      break;
    default:
      break;
  }
}
