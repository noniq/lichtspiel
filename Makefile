TARGET        = Lichtspiel
ARDMK_DIR     = /usr/local/opt/arduino-mk
MONITOR_PORT  = /dev/cu.usbmodemFA1231

ISP_PROG	   = stk500v1
ISP_PORT     = /dev/cu.usbmodemFA1231
AVRDUDE_ISP_BAUDRATE = 57600

BOARD_TAG     = uno
ARDUINO_QUIET = 1
ARDUINO_LIBS = EEPROM FastLED

CPPFLAGS = -DDEV

include ${ARDMK_DIR}/Arduino.mk

