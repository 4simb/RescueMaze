# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS

threshold_black = (0, 64)

def inThreshold(n):
    return n >= threshold_black[0] and n <= threshold_black[1]

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
templateH = image.Image("\hnew.pgm")
templateU = image.Image("\yinewnew.pgm")
templateS = image.Image("\snewnew.pgm")
#xywh

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    copies = []
    xList = []
    yList = []
    #img = img.copy(roi = (0, int(0.3 * img.height()), img.width(), img.height()), copy_to_fb=img)
    for yb in img.find_blobs([threshold_black], area_threshold = 200, pixel_thereshold = 20000):#area_threshold = 2000):
        #copies.append(img.copy(x_size = 60, y_size = 60, roi = (yb.x(), yb.y(), yb.w(), yb.h())))
        #print("YES")#copies.append(img.copy(x_size = 100, y_size = 100, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.9 * yb.w()), int(1.9 * yb.h()))))
        #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())
        #copies.append(img.copy(roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.6 * yb.w()), int(1.6 * yb.h()))))#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), c, int(1.5 * yb.h()))))
        #img = img.copy(roi = (yb.w(), yb.h()))
        #img = img.copy(x_size = 60, y_size = 60, copy_to_fb=img)#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.5 * yb.w()), int(1.5 * yb.h())))
        #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())
        #copies.append(img.copy(roi = (yb.x(), yb.y(), yb.w(), yb.h())))
        copies.append(img.copy(roi = (yb.x(), yb.y(), yb.w(), yb.h())))
        xList.append(yb.x())
        yList.append(yb.y())

    #img.copy(copy_to_fb=img, x_size = 40, y_size = 40, roi = (int(0 * img.height()), int(0 * img.width()), int(1 * img.height()), int(1 * img.width())))
    #(int(0.25 * img.height()), int(0.25 * img.width()), int(0.75 * img.height()), int(0.75 * img.width()))

    index = 0
    for elements in copies:
        count = 0
        x = max(xList[index] + int(0.5 * elements.width()) - 3, 0)
        y =  elements.height()
        for obj in elements.find_blobs([threshold_black], roi = (max(int(0.5 * elements.width()) - 3, 0), 0, 6, elements.height()), area_threshold = 2):
            #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())
            count += 1
            img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = 0)

        index += 1
        #img.draw_rectangle(max(elements.x() + int(0.5 * elements.w()) - 3, 0), elements.y(), 6, elements.h()) #central
        #img.draw_rectangle(elements.x(), max(0, elements.y() + elements.h() - 5), elements.w(), 5) #down
