import sensor, image, time, pyb
from image import SEARCH_EX, SEARCH_DS
from pyb import UART

red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)
thresh = 10

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

threshold_black = (0, 18, -128, 127, 127, -128)
threshold_yellow = (100, 0, -128, 24, 32, 127)#(0, 100, -48, 127, -128, 45)#
threshold_green = (0, 100, -128, -15, -128, 35)#(0, 31, -128, -15, -16, 22)#
threshold_red = (0, 100, 24, 127, -128, 127)#(0, 100, -128, 14, -33, 80)#(0, 100, 31, 127, -23, 127)
# (42, 72, -18, 6, -18, 13)
messageOld = " "

sensor.reset()
sensor.set_contrast(1)              # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.RGB565) #GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (160x120)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
uart = UART(3, 115200)

while(True):
    #set_led_white()
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    #img.replace(img, vflip = True, hmirror = True)

    message = " "

    colorLetter = " "
    foundColor = False
    trueBlob = False
    prevBlob = False

    #COLOR START

    for redBlob in img.find_blobs([threshold_red], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
        if redBlob.w() / redBlob.h() > 3 / 2:
            continue
        trueBlob = redBlob
        foundColor = True
        colorLetter = "R"

    for greenBlob in img.find_blobs([threshold_green], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
        if greenBlob.w() / greenBlob.h() > 3 / 2:
            continue
        if trueBlob != False:
            if greenBlob.area() > trueBlob.area():
                trueBlob = greenBlob
                foundColor = True
                colorLetter = "G"
        else:
            trueBlob = greenBlob
            foundColor = True
            colorLetter = "G"

    for yellowBlob in img.find_blobs([threshold_yellow], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
        if yellowBlob.w() / yellowBlob.h() > 3 / 2:
            continue
        if trueBlob != False:
            if yellowBlob.area() > trueBlob.area():
                trueBlob = yellowBlob
                foundColor = True
                colorLetter = "Y"
        else:
            trueBlob = yellowBlob
            foundColor = True
            colorLetter = "Y"

    if foundColor:
        img.draw_rectangle(trueBlob.x(), trueBlob.y(), trueBlob.w(), trueBlob.h(), color = (255, 255, 255))
        print(colorLetter, trueBlob.x(), trueBlob.y())
        uart.write(colorLetter)
        message = colorLetter

    #COLOR EnD

    else:
        for letter in img.find_blobs([threshold_black], pixel_threshold = 2000, area_threshold = 1000, merge = True, margin = 100):#area_threshold = 2000):
            ratio = letter.w()/letter.h()
            if ratio < 0.4 or ratio > 2.5:
                continue
            #if lBlob.w()/lBlob.h() > 0.4 and yb.w()/yb.h() < 2.5:

            # true blob sizes
            bx = max(letter.x(), 0)
            by = max(letter.y(), 0)
            bw = min(img.width() - letter.x(), letter.w())
            bh = min(img.height() - letter.y(), letter.h())

            #count = 0
            #                 bw
            #    (bx, by) --------- (bx + bw, by)
            #        |                     |
            #        |                     |  bh
            #        |                     |
            #        |                     |
            #  (bx, by + bh) --- (bx + bw, by + bh)

            upRoi = bx, by, bw, int(bh/4)
            midRoi = bx, by + int(bh * 1 / 4), bw, int(bh/2)
            downRoi = bx, by + int(bh * 3 / 4), bw, int(bh/4)

            leftRoi = bx, by, bx + int(bw / 3), bh
            vertRoi = bx + int(bw / 3), by, int(bw/3), bh
            rightRoi = bx + int(bw * 2 / 3), by, bx + bw, bh

            img.draw_rectangle(bx + int(bw / 3), by, int(bw / 3), bh, color = (50, 50, 50))
            img.draw_rectangle(bx, by + int(bh / 3), bw, int(bh / 3), color = (50, 50, 50))

            # roi = region of interest

            upCount = 0
            for upBlob in img.find_blobs([threshold_black], roi = upRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                upCount += 1;
                img.draw_rectangle(upBlob.x(), upBlob.y(), upBlob.w(), upBlob.h(), color = (255, 255, 255))

            midCount = 0
            for midBlob in img.find_blobs([threshold_black], roi = midRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                midCount += 1;
                img.draw_rectangle(midBlob.x(), midBlob.y(), midBlob.w(), midBlob.h(), color = (255, 255, 255))

            downCount = 0
            for downBlob in img.find_blobs([threshold_black], roi = downRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                downCount += 1
                img.draw_rectangle(downBlob.x(), downBlob.y(), downBlob.w(), downBlob.h(), color = (255, 255, 255))

            leftCount = 0
            for leftBlob in img.find_blobs([threshold_black], roi = leftRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                leftCount += 1
                img.draw_rectangle(leftBlob.x(), leftBlob.y(), leftBlob.w(), leftBlob.h(), color = (255, 255, 255))

            vertCount = 0
            for vertBlob in img.find_blobs([threshold_black], roi = vertRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                vertCount += 1
                img.draw_rectangle(vertBlob.x(), vertBlob.y(), vertBlob.w(), vertBlob.h(), color = (255, 255, 255))

            rightCount = 0
            for rightBlob in img.find_blobs([threshold_black], roi = rightRoi, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                rightCount += 1
                img.draw_rectangle(rightBlob.x(), rightBlob.y(), rightBlob.w(), rightBlob.h(), color = (255, 255, 255))

            #determine letter
            #if midCount == 1 and upCount == 1 and vertCount >= 2 and rightCount == 2:
            if vertCount >= 2 and upCount == 1 and midCount == 1:
                print("S")
                message = "S"
                uart.write("S")
                #state = True
                foundLetter = True
                img.draw_rectangle(bx, by, bw, bh, color = (0, 0, 255))
            #elif midCount == 1 and upCount == 2 and vertCount == 1:
            elif leftCount == 1 and vertCount == 1 and rightCount == 1 and upCount == 2 and midCount == 1 and downCount == 2:
                print("H")
                message = "H"
                uart.write("H")
                foundLetter = True
                img.draw_rectangle(bx, by, bw, bh, color = (0, 0, 255))
            #elif midCount == 2 and upCount == 2 and vertCount == 1:
            elif leftCount == 1 and vertCount == 1 and rightCount == 1 and upCount == 2 and downCount == 1:
                print("U")
                message = "U"
                uart.write("U")
                foundLetter = True
                img.draw_rectangle(bx, by, bw, bh, color = (0, 0, 255))
                #red_led.on()

    if messageOld != " " and message ==  " ":
        uart.write("0")
        print("0")
    messageOld = message
    #if not(state):
    #    uart.write("1")
    if uart.any():
        uart.read()