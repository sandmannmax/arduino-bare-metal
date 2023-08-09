import serial

usbport = '/dev/tty.usbmodem213301'
baud = 9600

with serial.Serial(usbport, baud, timeout = 1) as ser:
    while True:
        x = ser.read()
        print(x)
