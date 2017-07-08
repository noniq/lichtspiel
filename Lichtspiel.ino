#include <avr/sleep.h>

#include "InteractionTimeout.h"
#include "LEDs.h"
#include "Rotary.h"
#include "Pulser.h"

#ifdef DEV
static const uint16_t INTERACTION_TIMEOUT_SECONDS = 20;
#define DEBUG(arg); Serial.println(arg);
#else
static const uint16_t INTERACTION_TIMEOUT_SECONDS = 120;
#define DEBUG(arg);
#endif
static const uint8_t NUM_BUTTONS = 5;
static const uint8_t BUTTON_PINS[NUM_BUTTONS] = {11, 12, 10, 13, 9};
static const uint8_t ANALOG_H_IN_PIN = 0;
static const uint8_t ANALOG_S_IN_PIN = 1;
static const uint8_t ANALOG_V_IN_PIN = 2;
static const uint8_t STANDBY_BUTTON_LED_PIN = 3;
static const uint8_t STANDBY_BUTTON_PIN = 8;

boolean standBy = true;
uint8_t lastButtonState[NUM_BUTTONS] = {HIGH};
boolean buttonIsUpdatingLED[NUM_BUTTONS] = {false};

// Generated with Ruby: (0..255).map{|i| (64 + (256 - 64) / 256.0 * i).round }.join(',')
uint8_t mapS[256] = {
  64,65,66,66,67,68,69,69,70,71,72,72,73,74,75,75,76,77,78,78,79,80,81,81,82,83,84,84,85,86,87,87,88,89,90,90,91,92,93,93,94,95,96,96,97,98,99,99,100,101,102,102,103,104,105,105,106,107,108,108,109,110,111,111,112,113,114,114,115,116,117,117,118,119,120,120,121,122,123,123,124,125,126,126,127,128,129,129,130,131,132,132,133,134,135,135,136,137,138,138,139,140,141,141,142,143,144,144,145,146,147,147,148,149,150,150,151,152,153,153,154,155,156,156,157,158,159,159,160,161,162,162,163,164,165,165,166,167,168,168,169,170,171,171,172,173,174,174,175,176,177,177,178,179,180,180,181,182,183,183,184,185,186,186,187,188,189,189,190,191,192,192,193,194,195,195,196,197,198,198,199,200,201,201,202,203,204,204,205,206,207,207,208,209,210,210,211,212,213,213,214,215,216,216,217,218,219,219,220,221,222,222,223,224,225,225,226,227,228,228,229,230,231,231,232,233,234,234,235,236,237,237,238,239,240,240,241,242,243,243,244,245,246,246,247,248,249,249,250,251,252,252,253,254,255,255
};

// Generated with Ruby: (0..255).map{|i| (i / 2.0 + 48).round }.join(',')
uint8_t mapV[256] = {
  32,33,33,34,34,35,36,36,37,37,38,39,39,40,40,41,42,42,43,43,44,45,45,46,46,47,48,48,49,50,50,51,51,52,53,53,54,54,55,56,56,57,57,58,59,59,60,60,61,62,62,63,63,64,65,65,66,66,67,68,68,69,69,70,71,71,72,72,73,74,74,75,75,76,77,77,78,78,79,80,80,81,82,82,83,83,84,85,85,86,86,87,88,88,89,89,90,91,91,92,92,93,94,94,95,95,96,97,97,98,98,99,100,100,101,101,102,103,103,104,104,105,106,106,107,107,108,109,109,110,110,111,112,112,113,114,114,115,115,116,117,117,118,118,119,120,120,121,121,122,123,123,124,124,125,126,126,127,127,128,129,129,130,130,131,132,132,133,133,134,135,135,136,136,137,138,138,139,139,140,141,141,142,142,143,144,144,145,146,146,147,147,148,149,149,150,150,151,152,152,153,153,154,155,155,156,156,157,158,158,159,159,160,161,161,162,162,163,164,164,165,165,166,167,167,168,168,169,170,170,171,171,172,173,173,174,174,175,176,176,177,178,178,179,179,180,181,181,182,182,183,184,184,185,185,186
};

uint8_t lastH, lastS, lastV;

InteractionTimeout interactionTimeout(INTERACTION_TIMEOUT_SECONDS);
Rotary rotary;
Rotary::Action action;
LEDs leds;
Pulser standBySwitchPulser(STANDBY_BUTTON_LED_PIN);


void setup() {
#ifdef DEV
  Serial.begin(57600);
#endif
  DEBUG("INIT");
  interactionTimeout.reset();
  leds.setup();
  rotary.setup();
  pinMode(STANDBY_BUTTON_PIN, INPUT_PULLUP);
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  lastH = 0;
  lastS = 0;
  lastV = 0;
  leds.off();
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

bool buttonDown(uint8_t index) {
  uint8_t state = digitalRead(BUTTON_PINS[index]);
  return state == LOW;
}

bool standByButtonPressed() {
  static uint8_t lastState;
  uint8_t state = digitalRead(STANDBY_BUTTON_PIN);
  if (state == LOW && lastState == HIGH) {
    lastState = LOW;
    return true;
  }
  lastState = state;
  return false;
}

void enterStandBy() {
  leds.saveStateToEEPROM();
  leds.off();
  standBy = true;
}

void leaveStandBy() {
  leds.loadStateFromEEPROM();
  standBySwitchPulser.steady();
  standBy = false;
  interactionTimeout.reset();
}

void loop() {
  if (standBy) {

    standBySwitchPulser.pulse();
    if (standByButtonPressed()) leaveStandBy();

  } else {

    uint8_t h = analogRead(ANALOG_H_IN_PIN) >> 2;
    uint8_t s = 255 - (analogRead(ANALOG_S_IN_PIN) >> 2);
    uint8_t v = 255 - (analogRead(ANALOG_V_IN_PIN) >> 2);
    leds.updateSingleLED(h, mapS[s], mapV[v]);
    if (abs(h - lastH) > 2 || abs(s - lastS) > 2 || abs(v - lastV) > 2) {
      interactionTimeout.reset();
      lastH = h;
      lastS = s;
      lastV = v;
    }

    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
      if (buttonPressed(i)) buttonIsUpdatingLED[i] = !leds.isStripLEDOn(i);
      if (buttonDown(i)) {
        if (buttonIsUpdatingLED[i]) {
          leds.updateStripLED(i, h, mapS[s], mapV[v]);
        } else {
          leds.turnOffStripLED(i);
        }
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

    if (standByButtonPressed() || interactionTimeout.timedOut()) enterStandBy();
  }
}
