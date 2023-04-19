# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time, pyb
from image import SEARCH_EX, SEARCH_DS
from pyb import UART

red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)
thresh = 10
countH = 0
countS = 0
countU = 0
countRed = 0
countBlue = 0
countYellow = 0

def set_led_red():
    red_led.on()
    green_led.off()
    blue_led.off()

def set_led_green():
    red_led.off()
    green_led.on()
    blue_led.off()

def set_led_blue():
    red_led.off()
    green_led.off()
    blue_led.on()

def set_led_white():
    red_led.on()
    green_led.on()
    blue_led.on()

def set_led_off():
    red_led.off()
    green_led.off()
    blue_led.off()


threshold_black = (0, 18, -128, 127, 127, -128)#(0, 33, -128, 127, 127, -128)#(26, 0, -128, 127, -128, 127)#(28, 0, -128, 127, 127, -128)
threshold_yellow = (100, 0, -128, 45, 32, 127)
threshold_green = (0, 100, -128, -15, 10, -128)#(0, 100, -128, -13, 42, -11)#(0, 100, -128, -11, -128, 127)
threshold_red = (0, 100, 31, 127, -23, 127)

#def inThreshold(n):
#    return bool(int(n) >= threshold_black[0] and int(n) <= threshold_black[1])

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.RGB565)#GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (160x120)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
#xywh


uart = UART(3, 115200)

messageOld = " "
while(True):
    #set_led_white()
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    img.replace(img, vflip = True, hmirror = True)
    #roii = (int(img.width() / 6), 0, int(3 * img.width() / 4), int(5 * img.height() / 6))
    copies = []
    xList = []
    yList = []
    message = " "
    state = False
    i = 0

    #YELLOW
    yellowMaxArea = 0
    for ybb in img.find_blobs([threshold_yellow], merge = True, margin = 10, area_threshold = 1200, pixel_threshold = 40):
        if ybb.area() > yellowMaxArea:
            yellowMaxArea = ybb.area()
            blobTrue = ybb
    if yellowMaxArea != 0:
        img.draw_rectangle(blobTrue.x(), blobTrue.y(), blobTrue.w(), blobTrue.h(), color = (255, 255, 255))
        print("Y")
        message = "Y"
        uart.write("Y")
        state = True


    #GREEN
    greenMaxArea = 0
    for ybb in img.find_blobs([threshold_green], merge = True, margin = 10, area_threshold = 1200, pixel_threshold = 40):
        if ybb.area() > greenMaxArea:
            greenMaxArea = ybb.area()
            blobTrue = ybb
    if greenMaxArea != 0:
        img.draw_rectangle(blobTrue.x(), blobTrue.y(), blobTrue.w(), blobTrue.h(), color = (255, 255, 255))
        print("G")
        uart.write("G")
        state = True
        message = "G"

    #RED
    redMaxArea = 0
    for ybb in img.find_blobs([threshold_red], merge = True, margin = 10, area_threshold = 1200, pixel_threshold = 40):
        if ybb.area() > redMaxArea:
            redMaxArea = ybb.area()
            blobTrue = ybb
    if redMaxArea != 0:
        img.draw_rectangle(blobTrue.x(), blobTrue.y(), blobTrue.w(), blobTrue.h(), color = (255, 255, 255))
        print("R")
        message = "R"
        uart.write("R")
        state = True

    if not(state):
        for yb in img.find_blobs([threshold_black], pixel_threshold = 2000, area_threshold = 1000, merge = True, margin = 100):#area_threshold = 2000):
            if yb.w()/yb.h() > 0.6 and yb.w()/yb.h() < 1.67:
                #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = (255, 255, 255))
                #elements = img.copy(roi = (yb.x(), yb.y(), yb.w(), yb.h()))

                xList = yb.x()
                yList = yb.y()
                count = 0
                roi1 = (max(xList + int(0.5 * yb.w()) - 5, 0), yList, 10, yb.h())
                #MIDDLE
                roi2 = (max(0, xList), max(0, yList + int(0.5 * yb.h()) - 2), min(img.width(), yb.w()), 30)
                count2 = 0
                for ybN in img.find_blobs([threshold_black], roi = roi2, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                    count2 += 1;
                    img.draw_rectangle(ybN.x(), ybN.y(), ybN.w(), ybN.h(), color = (255, 255, 255))

                #UP
                roi3 = (max(0, xList - 3), max(yList - 3, 0), min(img.width(), yb.w() + 6), 25)
                count3 = 0
                for ybN in img.find_blobs([threshold_black], roi = roi3, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                    count3 += 1;
                    img.draw_rectangle(ybN.x(), ybN.y(), ybN.w(), ybN.h(), color = (255, 255, 255))
                if count2 == 1 and count3 == 1:
                    print("S")
                    message = "S"
                    uart.write("S")
                    state = True
                    img.draw_rectangle(xList, yList, yb.w(), yb.h(), color = (0, 0, 255))
                    #set_led_white()
                elif count2 == 1 and count3 == 2:
                    print("H")
                    message = "H"
                    uart.write("H")
                    state = True
                    img.draw_rectangle(xList, yList, yb.w(), yb.h(), color = (0, 0, 255))
                    #red_led.on()
                elif count2 == 2 and count3 == 2:
                    print("U")
                    message = "U"
                    uart.write("U")
                    state = True
                    img.draw_rectangle(xList, yList, yb.w(), yb.h(), color = (0, 0, 255))
                    #red_led.on()

    if messageOld != " " and message ==  " ":
        uart.write("0")
        print("0")
    messageOld = message
    #if not(state):
    #    uart.write("1")
    if uart.any():
        uart.read()
