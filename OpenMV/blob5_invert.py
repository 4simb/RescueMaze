# Untitled - By: balakirskiyav.24 - Ср сен 21 2022

import sensor, image, time

#threshold_y = (25, 94, 31, 127, -3, 127)
threshold_y = (32, 75, 30, 127, 32, 86)
threshold_ii = (0, 100, -1, 127, 0, 124)
threshold_box = (0, 71, -3, 127, -128, -15)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    #centralsX = []
    #centralsY = []
    summX = 0
    summY = 0
    summW = 0
    summH = 0

    count = 0

    for yb in img.find_blobs([threshold_box], pixels_threshold = 450, merge=True, margin=1000):#area_threshold = 2000):
        #if yb.pixels() > maxi:
        #    maxi = yb.pixels()
        #    nn = yb
        #blobsY.append(yb)
        img.draw_rectangle(yb.rect())
        img.draw_cross(yb.cx(), yb.cy())
        img.draw_line(0, 0, yb.cx(), yb.cy())

        summX += yb.x()
        summY += yb.y()
        summW += yb.w()
        summH += yb.h()

    maxi = 0
    maxiBlob = []
    if not(summW <= 40 or summH <= 40 or summX <= 30 or summY <= 30):
        for ybb in img.find_blobs([threshold_box], pixels_threshold = 0, roi = (summX + 7, summY + 7, summW - 10, summH - 10), invert = True):#area_threshold = 2000):
            if ybb.pixels() > maxi:
                maxi = ybb.pixels()
                maxiBlob = ybb
            #img.draw_rectangle(ybb.rect(), color = (0, 0, 0), thickness = 5)
            #img.draw_cross(ybb.cx(), ybb.cy(), color = (0, 0, 0))
            #img.draw_line(0, 0, ybb.cx(), ybb.cy())

    if maxiBlob != []:
        img.draw_rectangle(maxiBlob.rect(), color = (0, 0, 0), thickness = 1)
        thresholdFirst = summW / 3

        if maxiBlob.x() <= summX + thresholdFirst:
            img.draw_rectangle((summX, summY, int(summW / 3), summH), color = (255, 127, 0), thickness = 2)
        if maxiBlob.x() + maxiBlob.h() >= summX + 2 * thresholdFirst:
            img.draw_rectangle((summX + 2 * int(summW / 3), summY, int(summW / 3), summH), color = (127, 127, 127), thickness = 2)

        if maxiBlob.x() <= summX + thresholdFirst and maxiBlob.x() + maxiBlob.h() >= summX + thresholdFirst:
            img.draw_rectangle((summX + int(summW / 3), summY, int(summW / 3), summH), color = (127, 0, 127), thickness = 2)
        if maxiBlob.x() > summX + thresholdFirst and maxiBlob.x() <= summX + 2 * thresholdFirst:
            img.draw_rectangle((summX + int(summW / 3), summY, int(summW / 3), summH), color = (127, 0, 127), thickness = 2)
        #elif maxiBlob.x() <= summX + 2 * thresholdFirst:
        #    img.draw_rectangle((summX + int(summW / 3), summY, int(summW / 3), summH), color = (127, 0, 127), thickness = 2)
        #else
        #    img.draw_rectangle((summX + 2 * int(summW / 3), summY, int(summW / 3), summH), color = (127, 0, 127), thickness = 2)

        #if maxiBlob.x + maxiBlob.h >= thresholdFirst and maxiBlob.x + maxiBlob.h < 2 * thresholdFirst:
        #    img.draw_rectangle((summX + int(summW / 3), summY, int(summW / 3), summH), color = (127, 0, 127), thickness = 2)
        #if maxiBlob.x + maxiBlob.h >= thresholdFirst and maxiBlob.x + maxiBlob.h < 3 * thresholdFirst:

    #if count != 0:
        #img.draw_cross(int(summX / count), int(summY / count), color = (255, 0, 0))

    print(clock.fps())
