# Untitled - By: balakirskiyav.24 - Ср сен 21 2022

import sensor, image, time

#threshold_y = (25, 94, 31, 127, -3, 127)
threshold_y = (32, 75, -128, 127, 32, 86)
threshold_box = (100, 12, -35, 127, -128, -28)

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
    for yb in img.find_blobs([threshold_y], pixels_threshold = 1000):#area_threshold = 2000):
        if yb.pixels() > maxi:
            maxi = yb.pixels()
            nn = yb
        blobsY.append(yb)
    try:
        #img.draw_rectangle(nn.rect())
        #img.draw_cross(nn.cx(), nn.cy())
        #img.draw_line(0, 0, nn.cx(), nn.cy())
    except: pass

    blobsBox = []
    nnn = []
    maxi = 0
    for bb in img.find_blobs([threshold_box], area_threshold = 2000):#area_threshold = 2000):
        if bb.pixels() > maxi:
            maxi = bb.pixels()
            nnn = bb
        blobsBox.append(bb)
    try:
        img.draw_rectangle(nnn.rect())
        img.draw_cross(nnn.cx(), nnn.cy())
        img.draw_line(0, 0, nn.cx(), nnn.cy())
        img.draw_rectangle(nn.rect())
        img.draw_cross(nn.cx(), nn.cy())
        img.draw_line(0, 0, nn.cx(), nn.cy())
    except: pass

    print(clock.fps())
