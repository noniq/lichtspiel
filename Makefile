TARGET        = Lichtspiel
ARDMK_DIR     = /usr/local/opt/arduino-mk
MONITOR_PORT  = /dev/cu.usbmodem1421

ISP_PROG	   = stk500v1
ISP_PORT     = /dev/cu.usbmodem1421
AVRDUDE_ISP_BAUDRATE = 57600

BOARD_TAG     = uno
ARDUINO_QUIET = 1
ARDUINO_LIBS = EEPROM FastLED

include ${ARDMK_DIR}/Arduino.mk

