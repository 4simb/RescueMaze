# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS

threshold_black = (0, 47)

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
templateH = image.Image("\hnew.pgm")
templateS = image.Image("\snew.pgm")
templateU = image.Image("\cpp.pgm")
#xywh

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    copies = []
    for yb in img.find_blobs([threshold_black], area_threshold = 400):#area_threshold = 2000):
        #copies.append(img.copy(x_size = 60, y_size = 60, roi = (yb.x(), yb.y(), yb.w(), yb.h())))
        print("YES")#copies.append(img.copy(x_size = 100, y_size = 100, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.9 * yb.w()), int(1.9 * yb.h()))))

        copies.append(img.copy(x_size = 60, y_size = 60))#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.5 * yb.w()), int(1.5 * yb.h()))))
        img = img.copy(x_size = 60, y_size = 60, copy_to_fb=img)#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.5 * yb.w()), int(1.5 * yb.h())))
        #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())

    #img.copy(copy_to_fb=img, x_size = 40, y_size = 40, roi = (int(0 * img.height()), int(0 * img.width()), int(1 * img.height()), int(1 * img.width())))
    #(int(0.25 * img.height()), int(0.25 * img.width()), int(0.75 * img.height()), int(0.75 * img.width()))

    for elements in copies:
        #print(elements.width())
        #print(elements.height())
        findH = elements.find_template(templateH, 0.65, step = 2, search = SEARCH_EX)
        findU = elements.find_template(templateU, 0.65, step = 2, search = SEARCH_EX)
        findS = elements.find_template(templateS, 0.38, step = 2, search = SEARCH_EX)

        if findH:
            print("H")
            img.draw_rectangle(findH)
        if findU:
            print("U")
            img.draw_rectangle(findU)
        if findS:
            print("S")
            img.draw_rectangle(findS)



