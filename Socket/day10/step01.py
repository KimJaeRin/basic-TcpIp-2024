import RPi.GPIO as GPIO
import time

steps = [4, 17, 27, 22]
GPIO.setmode(GPIO.BCM)

for stepPin in steps:
	GPIO.setup(stepPin, GPIO.OUT)
	GPIO.output(stepPin, 0)

try:
	while 1:
		GPIO.output(steps[0], 0)
		GPIO.output(steps[1], 1)
		GPIO.output(steps[2], 0)
		GPIO.output(steps[3], 0)
		time.sleep(1)
		GPIO.output(steps[0], 0)
		GPIO.output(steps[1], 0)
		GPIO.output(steps[2], 1)
		GPIO.output(steps[3], 0)
		time.sleep(0.1)
		GPIO.output(steps[0], 0)
		GPIO.output(steps[1], 1)
		GPIO.output(steps[2], 0)
		GPIO.output(steps[3], 0)
		time.sleep(0.1)
		GPIO.output(steps[0], 1)
		GPIO.output(steps[1], 0)
		GPIO.output(steps[2], 0)
		GPIO.output(steps[3], 0)
		time.sleep(0.1)

except KeyboardInterrupt:
	    GPIO.cleanup ()

