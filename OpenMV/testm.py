# Untitled - By: balakirskiyav.24 - Сб дек 3 2022

import sensor, image, time, pyb
from image import SEARCH_EX, SEARCH_DS
from pyb import Timer
from machine import Pin

threshold_black = (0, 77)
kp = 2.5
kd = 10
errOld = 0

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

timer = pyb.Timer(4, freq=1000)
left1 = timer.channel(1, pyb.Timer.PWM, pin = pyb.Pin("P7"))
left2 = timer.channel(2, pyb.Timer.PWM, pin = pyb.Pin("P8"))
timer2 = pyb.Timer(2, freq=1000)
right1 = timer2.channel(3, pyb.Timer.PWM, pin = pyb.Pin("P4"))
right2 = timer2.channel(4, pyb.Timer.PWM, pin = pyb.Pin("P5"))

#P4_P5

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()

    left1.pulse_width_percent(50)
    left2.pulse_width_percent(0)
    right1.pulse_width_percent(50)
    right2.pulse_width_percent(0)
    pyb.delay(1)
