TARGET=serial
MCU=atmega328p
SOURCES=main.c

PROGRAMMER=arduino
PORT=-P/dev/tty.usbmodem213301
BAUD=-b115200

OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-c -Os -DF_CPU=16000000UL
LDFLAGS=

default:
	avr-gcc $(CFLAGS) -mmcu=$(MCU) $(SOURCES)
	avr-gcc $(LDFLAGS) -mmcu=$(MCU) -o $(TARGET).bin $(OBJECTS)
	avr-objcopy -O ihex -R .eeprom $(TARGET).bin $(TARGET).hex
	avrdude -F -V -c $(PROGRAMMER) -p $(MCU) $(PORT) $(BAUD) -U flash:w:$(TARGET).hex

clean:
	rm $(OBJECTS)
	rm $(TARGET).bin
	rm $(TARGET).hex

