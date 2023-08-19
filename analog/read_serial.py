import serial

usbport = '/dev/tty.usbmodem213301'
baud = 9600

buffer = []
packet_length = 2

def process():
    global buffer
    global packet_length
    if len(buffer) < 4 + packet_length:
        return
    startup = 0
    for i in range(len(buffer)):
        if startup >= 4:
            if len(buffer) <= i + packet_length - 1:
                return
            process_values(buffer[i:i+packet_length])
            buffer = buffer[i+packet_length:]
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
    a = int.from_bytes(v[1] + v[0], "big")
    a *= (5. / 1023.)
    print(f"Analog voltage: {a:.2f} V")

with serial.Serial(usbport, baud, timeout = 1) as ser:
    while True:
        buffer.append(ser.read())
        process()


