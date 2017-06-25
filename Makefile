TARGET        = Lichtspiel
ARDMK_DIR     = /usr/local/opt/arduino-mk
MONITOR_PORT  = /dev/cu.usbmodem1421

BOARD_TAG     = uno
ARDUINO_QUIET = 1
ARDUINO_LIBS = FastLED

include ${ARDMK_DIR}/Arduino.mk

