#interrupt

import RPi.GPIO as GPIO
import time

#핀 설정
led = 21
switch = 6

intFlag = False

GPIO.setmode(GPIO.BCM)
GPIO.setup(led, GPIO.OUT)
GPIO.setup(switch, GPIO.IN)

def ledblink(channel):
		global intFlag
		if intFlag == False:
			 GPIO.output(led, True)
			 intFlag = True
		else:
			 GPIO.output(led, False)
			 intFlag = False

GPIO.add_event_detect(switch, GPIO.RISING, callback=ledblink)

try:
	 while True:
	 		pass
except KeyboardInterrupt:
		GPIO.cleanup()
