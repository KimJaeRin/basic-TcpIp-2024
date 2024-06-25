import RPi.GPIO as GPIO
import time

RED_PIN = 21
GREEN_PIN = 16
BLUE_PIN = 20
SWITCH_PIN = 6

GPIO.setmode(GPIO.BCM)

GPIO.setup(RED_PIN, GPIO.OUT)
GPIO.setup(GREEN_PIN, GPIO.OUT)
GPIO.setup(BLUE_PIN, GPIO.OUT)

GPIO.setup(SWITCH_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

red_state = False
green_state = False
blue_state = False

try:
    while True:
        if GPIO.input(SWITCH_PIN) == GPIO.LOW:
            red_state = not red_state
            green_state = not green_state
            blue_state = not blue_state

            GPIO.output(RED_PIN, red_state)
            GPIO.output(GREEN_PIN, green_state)
            GPIO.output(BLUE_PIN, blue_state)

        time.sleep(0.5)

except KeyboardInterrupt:
    GPIO.cleanup()
