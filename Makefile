DIR=.
BOARD=arduino:avr:mega
DEV=/dev/ttyUSB0

all:
	arduino-cli compile -b $(BOARD) $(DIR)

upload:
	arduino-cli upload -b $(BOARD) -p $(DEV)
