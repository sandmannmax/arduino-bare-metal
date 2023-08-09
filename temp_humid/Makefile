default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o temp_humid.o temp_humid.c
	avr-gcc -o temp_humid.bin temp_humid.o
	avr-objcopy -O ihex -R .eeprom temp_humid.bin temp_humid.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/tty.usbmodem213301 -b 115200 -U flash:w:temp_humid.hex
