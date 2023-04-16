# Untitled - By: balakirskiyav.24 - Сб дек 3 2022

import sensor, image, time, pyb
import math
from image import SEARCH_EX, SEARCH_DS
from pyb import Timer
from machine import Pin

threshold_black = (0, 53)
kp = 1
kd = 10
errOld = 11

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

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()

    maxiUp = 0
    upBlob = []
    for yb in img.find_blobs([threshold_black], merge = True, margin = 300, roi = (0, 0, img.width(), int(0.5 * img.height()))):
        if yb.pixels() > maxiUp:
            maxiUp = yb.pixels()
            upBlob = yb

    maxiDown = 0
    downBlob = []
    for yb in img.find_blobs([threshold_black], merge = True, margin = 300, roi = (0, int(0.5 * img.height()), img.width(), int(0.5 * img.height()))):
        if yb.pixels() > maxiDown:
            maxiDown = yb.pixels()
            downBlob = yb

    if downBlob != [] and upBlob != []:
        img.draw_line(upBlob.cx(), upBlob.cy(), downBlob.cx(), downBlob.cy())
        err = upBlob.cx() - downBlob.cx();
        p = err * kp
        d = (err - errOld) * kd
        u = p + d
        u *= 0.05
        if u > 6:
            u = 6
        elif u < -6:
            u = -6
        errOld = err
        #if downBlob.cx() < 0.5 * img.height():
        leftU = 13 + u - (0.5 * img.width() - downBlob.cx()) * 0.071
        rightU = 13 - u + (0.5 * img.width() - downBlob.cx()) * 0.071

        if leftU >= 40:
            left1.pulse_width_percent(40)
            left2.pulse_width_percent(0)
        elif leftU >= 0:
            left1.pulse_width_percent(int(leftU))
            left2.pulse_width_percent(0)
        elif leftU < 0 and leftU > -40:
            left1.pulse_width_percent(0)
            left2.pulse_width_percent(abs(int(leftU)))
        else:
            left1.pulse_width_percent(0)
            left2.pulse_width_percent(40)

        if rightU >= 40:
            right1.pulse_width_percent(40)
            right2.pulse_width_percent(0)
        elif rightU >= 0:
            right1.pulse_width_percent(int(rightU))
            right2.pulse_width_percent(0)
        elif rightU < 0 and rightU > -40:
            right1.pulse_width_percent(0)
            right2.pulse_width_percent(abs(int(rightU)))
        else:
            right1.pulse_width_percent(0)
            right2.pulse_width_percent(40)
    pyb.delay(1)
