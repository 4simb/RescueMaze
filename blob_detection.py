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

threshold_black = (0, 19, -18, 127, -128, 4)#(0, 11, -35, 127, -128, 127)
threshold_yellow = (19, 100, -128, 24, 39, 127)
threshold_green = (0, 21, -128, -8, -128, 34)
threshold_red = (0, 60, 27, 127, 24, 127)
messageOld = " "

sensor.reset()
sensor.set_contrast(1)
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.RGB565) #GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (160x120)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
uart = UART(3, 115200)

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.replace(img, vflip = True, hmirror = True)

    message = " "

    colorLetter = " "
    foundColor = False
    trueBlob = False

    #COLOR START

    for redBlob in img.find_blobs([threshold_red], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
        trueBlob = redBlob
        foundColor = True
        colorLetter = "R"

    for greenBlob in img.find_blobs([threshold_green], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
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
        if trueBlob.w() / trueBlob.h() > 2:
            continue
        img.draw_rectangle(trueBlob.x(), trueBlob.y(), trueBlob.w(), trueBlob.h(), color = (255, 0, 255))
        print(colorLetter, trueBlob.x(), trueBlob.y())
        uart.write(colorLetter)
        message = colorLetter

    #COLOR EnD

    else: #no color found
        for letter in img.find_blobs([threshold_black], pixel_threshold = 2000, area_threshold = 1000, merge = True, margin = 100):#area_threshold = 2000):
            ratio = letter.w()/letter.h()
            if ratio < 0.4 or ratio > 2.5:
                continue

            # true blob sizes
            bx = max(letter.x(), 0)
            by = max(letter.y(), 0)
            bw = min(img.width() - letter.x(), letter.w())
            bh = min(img.height() - letter.y(), letter.h())

            upRoi = bx, by, bw, int(bh/4)
            midRoi = bx, by + int(bh * 1 / 4), bw, int(bh/2)
            downRoi = bx, by + int(bh * 3 / 4), bw, int(bh/4)

            leftRoi = bx, by, int(bw / 3), bh
            vertRoi = bx + int(bw / 3), by, int(bw/3), bh
            rightRoi = bx + int(bw * 2 / 3), by, bx + bw, bh

            #count blobs in 6 sectors
            upBlob = 0; midBlob = 0; downBlob = 0; leftBlob = 0; vertBlob = 0; rightBob = 0
            upCount = 0; midCount = 0; downCount = 0; leftCount = 0; vertCount = 0; rightCount = 0

            blobAreaThreshold = 100;

            for upBlob in img.find_blobs([threshold_black], roi = upRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                upCount += 1;
                img.draw_rectangle(upBlob.x(), upBlob.y(), upBlob.w(), upBlob.h(), color = (255, 255, 255))

            for midBlob in img.find_blobs([threshold_black], roi = midRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                midCount += 1;
                img.draw_rectangle(midBlob.x(), midBlob.y(), midBlob.w(), midBlob.h(), color = (255, 255, 255))

            for downBlob in img.find_blobs([threshold_black], roi = downRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                downCount += 1
                img.draw_rectangle(downBlob.x(), downBlob.y(), downBlob.w(), downBlob.h(), color = (255, 255, 255))

            for leftBlob in img.find_blobs([threshold_black], roi = leftRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                leftCount += 1
                img.draw_rectangle(leftBlob.x(), leftBlob.y(), leftBlob.w(), leftBlob.h(), color = (255, 255, 255))

            for vertBlob in img.find_blobs([threshold_black], roi = vertRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                vertCount += 1
                img.draw_rectangle(vertBlob.x(), vertBlob.y(), vertBlob.w(), vertBlob.h(), color = (255, 255, 255))

            for rightBlob in img.find_blobs([threshold_black], roi = rightRoi, area_threshold = blobAreaThreshold, pixel_threshold = 200, x_stride = 1, merge = True, margin = 10):
                rightCount += 1
                img.draw_rectangle(rightBlob.x(), rightBlob.y(), rightBlob.w(), rightBlob.h(), color = (255, 255, 255))

            img.draw_rectangle(bx + int(bw / 3), by, int(bw / 3), bh, color = (0, 200, 200))
            img.draw_rectangle(bx, by + int(bh / 3), bw, int(bh / 3), color = (0, 200, 200))

            #determine letter
            sCondition = (vertCount >= 2 and rightCount >= 2 and leftCount >= 2) or (upCount == 1 and midCount == 2 and downCount == 1)
            hCondition = leftCount == 1 and vertCount == 1 and rightCount == 1 and upCount == 2 and midCount == 1 and downCount == 2
            uCondition = leftCount == 1 and vertCount == 1 and downCount == 1 and midCount == 2 and upCount == 2

            if (leftCount, vertCount, rightCount, upCount, midCount, downCount) == (1, 1, 1, 1, 1, 1):
                if midBlob.w() / downBlob.w() > 2:
                    hCondition = True
                    uCondition = False
                elif downBlob.w() / midBlob.w() > 2:
                    uCondition = True
                    hCondition = False

            recLetter = 0;

            if sCondition:
                recLetter = "S"
            elif hCondition:
                recLetter = "H"
            elif uCondition:
                recLetter = "U"

            if recLetter != 0:
                foundLetter = True;
                print(recLetter)
                message = recLetter
                uart.write(recLetter)
                img.draw_rectangle(bx, by, bw, bh, color = (0, 0, 255))

    if messageOld != " " and message ==  " ":
        uart.write("0")
        print("0")
    messageOld = message
    #if not(state):
    #    uart.write("1")
    if uart.any():
        uart.read()
