import RPi.GPIO as GPIO
import time

switch = 6
RED = 21
BLUE = 20
GREEN = 16

GPIO.setmode(GPIO.BCM)
GPIO.setup(switch, GPIO.IN)
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(BLUE, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)

try:
		while True:
			if	GPIO.input(switch) == False:
					print("pushed")
					
					time.sleep(0.5)
except KeyboardInterrupt:
		GPIO.cleanup()

