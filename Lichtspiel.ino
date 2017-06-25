#include "Lichtspiel.h"
#include "LEDs.h"
#include "Rotary.h"

#include <Adafruit_NeoPixel.h>

static const uint8_t SINGLE_RGB_LED_PIN = 6;
static const uint8_t LED_STRIP_PIN = 5;
static const uint8_t LED_STRIP_NUM_LEDS = 24;

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
byte mapping[256];
Rotary rotary;
Rotary::Action action;
LEDs leds(SINGLE_RGB_LED_PIN, LED_STRIP_PIN, LED_STRIP_NUM_LEDS);

void setup() {
  leds.init();
  // Serial.begin(115200);
  // for (int i = 0; i < 256; i++) {
  //   mapping[i] = (double)i * i / (255.0);
  //   Serial.println(mapping[i]);
  // }
}

void loop() {
  leds.updateSingleLED(analogRead(ANALOG_R_IN_PIN) >> 2, analogRead(ANALOG_G_IN_PIN) >> 2, analogRead(ANALOG_B_IN_PIN) >> 2);
  delay(20);
// #ifdef TEST_SLIDER
//   sensorValue = ;
//   analogWrite(ledPin, mapping[sensorValue]);
//
// #ifdef DEBUG
//   Serial.println(sensorValue);
//   delay(100);
// #endif
//
// #else
//   action = rotary.waitForAction();
//   switch (action) {
//     case Rotary::LEFT:
//       if (sensorValue > 0) sensorValue -= 4;
//       break;
//     case Rotary::RIGHT:
//       if (sensorValue < 252) sensorValue += 4;
//       break;
//     default:
//       Serial.println("Unknown action");
//   }
//   analogWrite(ledPin, sensorValue);
// #endif
}
