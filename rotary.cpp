#include <Arduino.h>
#include "Rotary.h"

uint8_t Rotary::readEnc() {
  return (bit_is_set(port, pinA) ? 0b01 : 0b00) | (bit_is_set(port, pinB) ? 0b10 : 0b00);
}

Rotary::Rotary(uint8_t _pinA, uint8_t _pinB, uint8_t _port) {
  pinA = _pinA;
  pinB = _pinB;
  port = _port;
  _prevPos = readEnc();
  _flags = 0;
}

void Rotary::setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
}

Rotary::Action Rotary::read() {
  Action action = NONE;
  uint8_t curPos = readEnc();

  if (curPos != _prevPos) {

    if (_prevPos == 0b00) {
      if (curPos == 0b01 || curPos == 0b10) { // First edge
        _flags |= curPos;
      }
    }

    if (curPos == 0b11) { // “Middle” of a step
      _flags |= 0b10000;
    } else if (curPos == 0b00) { // Final edge
      if (_prevPos == 0b10) {
        _flags |= 0b00100;
      } else if (_prevPos == 0b01) {
        _flags |= 0b01000;
      }

      // check the first and last edge
      // or maybe one edge is missing, if missing then require the middle state
      // this will reject bounces and false movements
      if (bit_is_set(_flags, 0) && (bit_is_set(_flags, 2) || bit_is_set(_flags, 4))) {
        action = RIGHT;
      }
      else if (bit_is_set(_flags, 2) && (bit_is_set(_flags, 0) || bit_is_set(_flags, 4))) {
        action = RIGHT;
      }
      else if (bit_is_set(_flags, 1) && (bit_is_set(_flags, 3) || bit_is_set(_flags, 4))) {
        action = LEFT;
      }
      else if (bit_is_set(_flags, 3) && (bit_is_set(_flags, 1) || bit_is_set(_flags, 4))) {
        action = LEFT;
      }

      _flags = 0;
    }
  }
  _prevPos = curPos;
  return action;
}

Rotary::Action Rotary::waitForAction() {
  Action action;
  uint32_t startMillis = millis();
  while ((action = read()) == NONE && millis() - startMillis < TIMEOUT_MILLIS);
  return (action == NONE ? TIMEOUT : action);
}
