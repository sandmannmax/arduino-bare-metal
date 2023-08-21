import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import time

usbport = '/dev/tty.usbmodem213301'
baud = 9600

packet_length = 32
packet_prefix = b'\xf0\x0f\xf0\x0f'

buffer = b''
data_buffer = []
samples = 0

style.use('fivethirtyeight')

plot_range = [.4, .6]

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

def animate(i):
    global data_buffer
    read()
    xs = [x for x in range(len(data_buffer))]
    ys = [y for y in data_buffer]
    ax1.clear()
    plt.ylim(plot_range)
    ax1.plot(xs, ys, linewidth=0.5)
    plt.ylim(plot_range)



def process():
    global buffer
    global packet_length
    if len(buffer) < 2 * len(packet_prefix) + packet_length:
        return
    if packet_prefix in buffer:
        i1 = buffer.find(packet_prefix)
        i2 = buffer.find(packet_prefix, i1 + len(packet_prefix))
        if i1 != -1 and i2 != -1:
            packet = buffer[i1:i2-i1]
            packet = packet[len(packet_prefix):] # remove prefix
            process_packet(packet)
            buffer = buffer[i2:]

def process_packet(packet):
    global data_buffer
    global samples
    samples += packet_length / 2
    for i in range(packet_length // 2):
        a = int.from_bytes(packet[i*2:i*2+2], "big")
        a *= (5. / 1024)
        data_buffer.append(a)
    if len(data_buffer) > 1024:
        data_buffer = data_buffer[-1024:]

def read():
    global buffer
    buffer += ser.read(packet_length)
    process()

ser = serial.Serial(usbport, baud, timeout = 1)
ani = animation.FuncAnimation(fig, animate, interval=1)

plt.ylim(plot_range)
plt.show()
ser.close()
# with serial.Serial(usbport, baud, timeout = 1) as ser:
#     start = time.time()
#     while True:
#         read()
#         if samples > 1000:
#             break
#     end = time.time()
#     duration = end - start
#     samplerate = samples / duration
#     print("Samplerate: ", samplerate)
#         # print('B', data_buffer)


