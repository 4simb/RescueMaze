# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 500)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    #img.draw_line(0, 0, 319, 239, (250, 253, 18), 10)
    h = img.height()
    w = img.width()

    centerX = int(w / 2) - 1
    centerY = int(h) - 1

    img.set_pixel(centerX, centerY, (255, 255, 255))
    coordX = centerX
    coordY = centerY
    coordXOld = coordX
    coordYOld = coordY

    for i in range(1, centerX):
        coordX = centerX + i
        coordY = centerY - int(i * i / 20)
        if coordY < 0 or coordX >= w:
            break
        img.set_pixel(coordX, coordY, (255, 255, 255))
        img.draw_line(coordXOld, coordYOld, coordX, coordY, (255, 0, 0), 3)
        coordXOld = coordX
        coordYOld = coordY

    coordX = centerX
    coordY = centerY
    coordXOld = coordX
    coordYOld = coordY

    for i in range(1, centerX):
        coordX = centerX - i
        coordY = centerY - int(i * i / 20)
        if coordY < 0 or coordX >= w:
            break
        img.set_pixel(coordX, coordY, (255, 255, 255))
        img.draw_line(coordXOld, coordYOld, coordX, coordY, (255, 0, 0), 3)
        coordXOld = coordX
        coordYOld = coordY


    #img.draw_line(, 5 * y, , 5 * y)
    #img.draw_circle() krug
    print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                    # to the IDE. The FPS should increase once disconnected.
