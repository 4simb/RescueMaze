# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from image import SEARCH_EX, SEARCH_DS

sensor.reset()
sensor.set_contrast(1)                     # Reset and initialize the sensor.
sensor.set_gainceiling(16)
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.
template = image.Image("\hh2.pgm")

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    r = img.find_template(template, 0.55, step = 4, search = SEARCH_EX)
    if r:
        print(r[0])
        #img.draw_rectangle(r)
        #if img.get_pixel(r[0] + int(r[3] * 0.5), r[1] + int(r[2] * 0.5)) == (0, 0, 0):
        img.draw_rectangle(r)


    #print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                    # to the IDE. The FPS should increase once disconnected.
