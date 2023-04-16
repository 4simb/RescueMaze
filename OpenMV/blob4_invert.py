# Untitled - By: balakirskiyav.24 - Ср сен 21 2022

import sensor, image, time

#threshold_y = (25, 94, 31, 127, -3, 127)
threshold_y = (32, 75, 30, 127, 32, 86)
threshold_ii = (0, 100, -1, 127, 0, 124)
threshold_box = (0, 100, -35, 48, -128, -28)

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

    for ybb in img.find_blobs([threshold_box], pixels_threshold = 450, roi = (summX + 10, summY + 10, summW - 30, summH - 30), invert = True):#area_threshold = 2000):
        img.draw_rectangle(ybb.rect(), color = (0, 0, 0), thickness = 5)
        img.draw_cross(ybb.cx(), ybb.cy(), color = (0, 0, 0))
        img.draw_line(0, 0, ybb.cx(), ybb.cy())

    #if count != 0:
        #img.draw_cross(int(summX / count), int(summY / count), color = (255, 0, 0))

    print(clock.fps())
