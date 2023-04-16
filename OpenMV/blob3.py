# Untitled - By: balakirskiyav.24 - Ср сен 21 2022

import sensor, image, time

#threshold_y = (25, 94, 31, 127, -3, 127)
threshold_y = (32, 75, 30, 127, 32, 86)
threshold_box = (100, 12, -35, 127, -128, -28)

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
    count = 0

    for yb in img.find_blobs([threshold_y], pixels_threshold = 350, merge = True, margin = 3000):#area_threshold = 2000):
        #if yb.pixels() > maxi:
        #    maxi = yb.pixels()
        #    nn = yb
        #blobsY.append(yb)
        img.draw_rectangle(yb.rect())
        img.draw_cross(yb.cx(), yb.cy())
        img.draw_line(0, 0, yb.cx(), yb.cy())

        #summX += yb.cx()
        #summY += yb.cy()
        #count += 1

    #if count != 0:
        #img.draw_cross(int(summX / count), int(summY / count), color = (255, 0, 0))

    print(clock.fps())
