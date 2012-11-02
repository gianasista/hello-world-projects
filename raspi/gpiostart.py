# This script is a short hello world for GPIO usage.
# It uses a simple circuit with a LED
# BOARD-PIN 11 to LED long-leg
# BOARD-PIN 6 to LEDs resistor (at short leg)

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.OUT)

while True:
	GPIO.output(11, True)
	time.sleep(2)
	GPIO.output(11, False)
	time.sleep(2)
