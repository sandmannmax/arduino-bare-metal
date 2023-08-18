import serial

usbport = '/dev/tty.usbmodem213301'
baud = 9600

buffer = []

def process():
    global buffer
    if len(buffer) < 7:
        return
    startup = 0
    for i in range(len(buffer)):
        if startup >= 4:
            if len(buffer) <= i + 2:
                return
            process_values(buffer[i:i+3])
            buffer = buffer[i+3:]
        elif startup % 2 == 0:
            if buffer[i] == b'\xf0' and (startup == 0 or (i > 0 and buffer[i-1] == b'\x0f')):
                startup += 1
            else:
                startup = 0
        else:
            if buffer[i] == b'\x0f' and i > 0 and buffer[i-1] == b'\xf0':
                startup += 1
            else:
                startup = 0

def process_values(v):
    d = int.from_bytes(v[0], "big")
    a = int.from_bytes(v[2] + v[1], "big")
    a *= (5. / 1023.)
    # print("Analog voltage:", a)
    print(d, a)

with serial.Serial(usbport, baud, timeout = 1) as ser:
    while True:
        buffer.append(ser.read())
        process()


