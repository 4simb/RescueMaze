import time
from pyb import UART

# UART 3, and baudrate.
uart = UART(3, 115200)

while(True):
    uart.write("1")
    if (uart.any()):
        print(uart.read())
    time.sleep(1000)
#uart = UART(3, 115200)
#uart.write('hello')
#uart.read(5) # read up to 5 bytes
#time.sleep(1000)
