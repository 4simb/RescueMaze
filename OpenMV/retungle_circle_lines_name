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

    x = int(w / 10)
    y = int(h / 10)
    img.draw_rectangle(x, y, 8 * x, 8 * y, (0, 255, 0), 4)
    img.draw_line(5 * x, y, 5 * x, 9 * y, (255, 0, 0), 3)
    img.draw_line(5 * x - 4 * y, 5 * y, 5 * x + 4 * y, 5 * y, (255, 0, 0), 3)
    img.draw_circle(5 * x, 5 * y, 4 * y - 1, (255, 255, 255), 4)
    img.draw_string(0, 0, "BALAKIRSKIY ARKADIY", (255, 255, 255))
    #img.draw_line(, 5 * y, , 5 * y)
    #img.draw_circle() krug
    print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                    # to the IDE. The FPS should increase once disconnected.
