# Untitled - By: balakirskiyav.24 - Ср сен 21 2022

import sensor, image, time

#threshold_y = (25, 94, 31, 127, -3, 127)
threshold_y = (10, 100, 19, 111, -128, -17)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    blobsY = []
    nn = []
    maxi = 0
    for yb in img.find_blobs([threshold_y], area_threshold = 3000):
        if yb.pixels() > maxi:
            maxi = yb.pixels()
            nn = yb
        blobsY.append(yb)
    try:
        #for inBlobsY in blobsY:
        img.draw_rectangle(nn.rect())
        img.draw_cross(nn.cx(), nn.cy())
        img.draw_line(0, 0, nn.cx(), nn.cy())
    except: pass

    print(clock.fps())
