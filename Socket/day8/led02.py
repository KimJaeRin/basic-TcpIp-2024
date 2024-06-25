import RPi.GPIO as GPIO
import time

Red = 21
Blue = 20
Green = 16

#GPIO를 BCM모드로 설정
GPIO.setmode(GPIO.BCM)
#GPIO핀설정(입력/출력)
GPIO.setup(Red, GPIO.OUT)
GPIO.setup(Blue, GPIO.OUT)
GPIO.setup(Green, GPIO.OUT)

try:
		while True:
			GPIO.output(Red, False)
			time.sleep(1)
			GPIO.output(Red, True)
			time.sleep(1)
			GPIO.output(Green, False)
			time.sleep(1)
			GPIO.output(Green, True)
			time.sleep(1)
			GPIO.output(Blue, False)
			time.sleep(1)
			GPIO.output(Blue, True)
			time.sleep(1)

except KeyboardInterrupt:   # Ctrl + C
		GPIO.cleanup()
