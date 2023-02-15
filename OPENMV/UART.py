import sensor, image, time
from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()
uart = UART(3, 115200, timeout_char=1000)

while(True):
    clock.tick()
    img = sensor.snapshot()
    uart.write(0) #None
    uart.write(1) #H
    uart.write(2) #S
    uart.write(3) #U
    print(clock.fps())
