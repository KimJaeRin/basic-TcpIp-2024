import RPi.GPIO as GPIO
import time


piezo = 13
melody =[130, 138, 147, 165, 175, 196, 220, 247]

GPIO.setmode(GPIO.BCM)
GPIO.setup(piezo, GPIO.OUT)

Buzz = GPIO.PWM(piezo, 440)

try:
	while True:
		Buzz.start(50)      #duty 50
		for i in  range(0, len(melody)):
			Buzz.ChangeFrequency(melody[i])
			time.sleep(0.3)
		Buzz.stop()
		time.sleep(1)
		
except KeyboardInterrupt:
	GPIO.cleanup()
