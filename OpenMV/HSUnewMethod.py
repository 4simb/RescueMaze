# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS
from pyb import UART

threshold_black = (15, 0, -128, 127, -128, 127)
threshold_yellow = (0, 100, -128, 127, 127, 36)
threshold_green = (0, 100, -128, -9, -14, 17)#(0, 100, -128, -7, -128, 127)
threshold_red = (0, 100, 31, 127, -23, 127)

#def inThreshold(n):
#    return bool(int(n) >= threshold_black[0] and int(n) <= threshold_black[1])

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.RGB565)#GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (160x120)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
#xywh

uart = UART(3, 115200)

messageOld = " "
while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    roii = (int(img.width() / 6), 0, int(3 * img.width() / 4), int(5 * img.height() / 6))
    copies = []
    xList = []
    yList = []
    message = " "
    for yb in img.find_blobs([threshold_black], area_threshold = 400, roi =  roii):#area_threshold = 2000):
        if yb.pixels() > 20:
            copies.append(img.copy(roi = (yb.x(), yb.y(), yb.w(), yb.h())))
            xList.append(yb.x())
            yList.append(yb.y())

    state = False
    i = 0
    for elements in copies:
        count = 0
        roi1 = (max(xList[i] + int(0.5 * elements.width()) - 5, 0), yList[i], 10, elements.height())

        for yb in img.find_blobs([threshold_black], area_threshold = 0, roi = roi1):
            #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = (255, 255, 255))
            count += 1

        if count == 3:
            print("S")
            message = "S"
            uart.write("S")
            state = True
            img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height(), color = (0, 0, 255))
        elif count == 1:
            #MIDDLE
            roi2 = (max(0, xList[i]), max(0, yList[i] + int(0.5 * elements.height()) - 2), min(img.width(), elements.width()), 15)
            count2 = 0
            for yb in img.find_blobs([threshold_black], roi = roi2, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                count2 += 1;
                #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = (255, 255, 255))

            if count2 == 1 or count2 == 2:
                #DOWN
                roi3 = (max(0, xList[i] - 3), max(0, yList[i] + elements.height() - 7), min(img.width(), elements.width() + 6), 7)
                count3 = 0
                for yb in img.find_blobs([threshold_black], roi = roi3, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                    count3 += 1;
                    #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = (255, 255, 255))
                if count2 == 1 and count3 == 2:
                   print("H")
                   message = "H"
                   uart.write("H")
                   state = True
                   img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height(), color = (0, 0, 255))
        i += 1

    if not(state):
        #YELLOW
        yellowMaxArea = 0
        for ybb in img.find_blobs([threshold_yellow], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40, roi =  roii):
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
        #greenMaxArea = 0
        #for ybb in img.find_blobs([threshold_green], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40):
        #    if ybb.area() > greenMaxArea:
        #        greenMaxArea = ybb.area()
        #        blobTrue = ybb
        #if greenMaxArea != 0:
        #    img.draw_rectangle(blobTrue.x(), blobTrue.y(), blobTrue.w(), blobTrue.h(), color = (255, 255, 255))
        #    print("G")
        #    uart.write("G")
        #    state = True


        #RED
        redMaxArea = 0
        for ybb in img.find_blobs([threshold_red], merge = True, margin = 10, area_threshold = 700, pixel_threshold = 40, roi =  roii):
            if ybb.area() > redMaxArea:
                redMaxArea = ybb.area()
                blobTrue = ybb
        if redMaxArea != 0:
            img.draw_rectangle(blobTrue.x(), blobTrue.y(), blobTrue.w(), blobTrue.h(), color = (255, 255, 255))
            print("R")
            message = "R"
            uart.write("R")
            state = True

    if messageOld != " " and message ==  " ":
        uart.write("0")
    messageOld = message
    #if not(state):
    #    uart.write("1")
    if uart.any():
        uart.read()
