#include <Arduino.h>
#include "InteractionTimeout.h"

InteractionTimeout::InteractionTimeout(uint16_t seconds) {
  timeoutSeconds = seconds;
  reset();
}

void InteractionTimeout::reset() {
  lastInteractionMillis = millis();
}

boolean InteractionTimeout::timedOut() {
  return (millis() - lastInteractionMillis) / 1000 > timeoutSeconds;
}
