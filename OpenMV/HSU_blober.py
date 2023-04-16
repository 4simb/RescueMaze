# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS

threshold_black = (0, 82)

def inThreshold(n):
    return bool(int(n) >= threshold_black[0] and int(n) <= threshold_black[1])

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
#xywh

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    copies = []
    #img = img.copy(roi = (0, int(0.3 * img.height()), img.width(), img.height()), copy_to_fb=img)
    xList = []
    yList = []
    for yb in img.find_blobs([threshold_black], area_threshold = 400):#area_threshold = 2000):
        #copies.append(img.copy(x_size = 60, y_size = 60, roi = (yb.x(), yb.y(), yb.w(), yb.h())))
        #print("YES")#copies.append(img.copy(x_size = 100, y_size = 100, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.9 * yb.w()), int(1.9 * yb.h()))))
        #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())
        #copies.append(img.copy(roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.6 * yb.w()), int(1.6 * yb.h()))))#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), c, int(1.5 * yb.h()))))
        #img = img.copy(roi = (yb.w(), yb.h()))
        #img = img.copy(x_size = 60, y_size = 60, copy_to_fb=img)#, roi = (int(0.5 * yb.x()), int(0.5 * yb.y()), int(1.5 * yb.w()), int(1.5 * yb.h())))
        #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h())
        if yb.pixels() > 20 and yb.pixels() < 500:
            copies.append(img.copy(roi = (yb.x(), yb.y(), yb.w(), yb.h())))
            xList.append(yb.x())
            yList.append(yb.y())


    #img.copy(copy_to_fb=img, x_size = 40, y_size = 40, roi = (int(0 * img.height()), int(0 * img.width()), int(1 * img.height()), int(1 * img.width())))
    #(int(0.25 * img.height()), int(0.25 * img.width()), int(0.75 * img.height()), int(0.75 * img.width()))

    i = 0
    for elements in copies:
        #img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height())
        count = 0
        roi1 = (max(xList[i] + int(0.5 * elements.width()) - 3, 0), yList[i], 6, elements.height() )
        #x0 = max(xList[i] + int(0.5 * elements.width()) - 3, 0)
        #y0 = yList[i]
        #w0 = 6
        #h0 = elements.height()

        for yb in img.find_blobs([threshold_black], area_threshold = 10, roi = roi1):
            #img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = 255)
            count += 1

        if count == 3:
            print("S")
            img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height(), color = 123)
        elif count == 1:
            #MIDDLE
            roi2 = (max(0, xList[i] - 3), max(0, yList[i] + int(0.5 * elements.height()) - 5), min(img.width(), elements.width() + 6), 5)
            #img.draw_rectangle(max(0, xList[i] - 3), max(0, yList[i] + int(0.5 * elements.height()) - 5), min(img.width(), elements.width() + 6), 5)
            count2 = 0
            for yb in img.find_blobs([threshold_black], roi = roi2, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                count2 += 1;
                img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = 255)

            #DOWN
            roi3 = (max(0, xList[i] - 3), max(0, yList[i] + elements.height() - 7), min(img.width(), elements.width() + 6), 7)
            count3 = 0
            for yb in img.find_blobs([threshold_black], roi = roi3, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                count3 += 1;
                img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = 255)

            #UP
            roi4 = (max(0, xList[i] - 3), max(0, yList[i] - 1), min(img.width(), elements.width() + 5), 7)
            #img.draw_rectangle(max(0, xList[i] - 3), max(0, yList[i]), min(img.width(), elements.width() + 5), 5)
            count4 = 0
            for yb in img.find_blobs([threshold_black], roi = roi4, area_threshold = 0, pixel_threshold = 0, x_stride = 1, merge = True, margin = 10):
                count4 += 1;
                img.draw_rectangle(yb.x(), yb.y(), yb.w(), yb.h(), color = 255)

            if count2 == 1 and count3 == 2 and count4 == 2:
                print("H")
                img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height(), color = 123)
            elif count2 == 2 and count3 == 1 and count4 == 2:
                print("U")
                img.draw_rectangle(xList[i], yList[i], elements.width(), elements.height(), color = 123)
        i += 1

        #img.draw_rectangle(max(elements.x() + int(0.5 * elements.w()) - 3, 0), elements.y(), 6, elements.h()) #central
        #img.draw_rectangle(elements.x(), max(0, elements.y() + elements.h() - 5), elements.w(), 5) #down
