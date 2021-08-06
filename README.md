# Adafruit-TLC5947-raspberrypi
This repo has the ported code of Adafruits Arduino TLC5947 to the Raspberry pi.

## DISCLAIMER:
I DO NOT OWN ADAFRUITS LIBRARY, I simply ported the code from Arduino to Raspberry Pi.


## Prerequisits
wiringPi, see the [installation manual](http://wiringpi.com/download-and-install/) for instructions.


## Usage
Simply download the repo, make the files using the 'make' command, and execute the program by "./output".

## Notes
I used wiringPi even though it's recently been [deprecated](http://wiringpi.com/news/). The reason is because the function calls are basically exactly the same as Arduino's function calls.

A timer interrupt is used because I want to make a LED cube that outputs a static Frames per second, independently of how much work the CPU did between frames.

Thanks to Steve Manley on youtube (and [this video](https://www.youtube.com/watch?v=QRDKjxRvhq8&lc=UgyT6WEWXnQt8eD-bSZ4AaABAg.9QfAXblAYIi9QfIoz4nBmF&ab_channel=SteveManley)) for pointing me into this direction.
