# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS

threshold_black = (120, 255)

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
templateH = image.Image("\hh2.pgm")
templateS = image.Image("\sss.pgm")
templateU = image.Image("\cpptop.pgm")

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    copies = []
    for yb in img.find_blobs([threshold_black], pixels_threshold = 1000):#area_threshold = 2000):
        copies.append(img.copy(x_size = 60, y_size = 60, roi = (yb.x(), yb.y(), yb.h(), yb.w())))

    for elements in copies:
        #print(elements.width())
        #print(elements.height())
        findH = elements.find_template(templateH, 0.65, step = 4, search = SEARCH_EX)
        findU = elements.find_template(templateU, 0.65, step = 4, search = SEARCH_EX)
        findS = elements.find_template(templateS, 0.5, step = 4, search = SEARCH_EX)

        if findH:
            print("H")
            img.draw_rectangle(findH)
        if findU:
            print("U")
            img.draw_rectangle(findU)
        if findS:
            print("S")
            img.draw_rectangle(findS)
