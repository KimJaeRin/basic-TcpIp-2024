import RPi.GPIO as GPIO
from flask import Flask

led = 17

#GPIO를 BCM모드로 설정
GPIO.setmode(GPIO.BCM)
#GPIO핀설정(입력/출력)
GPIO.setup(led, GPIO.OUT)

app = Flask(__name__)

@app.route("/")
def fhello():
	return "Hello"


@app.route("/led/<state>")
	if state == "on":
			return "LED ON"

	elif state == "off":
 			return "LED OFF"

	elif state == "clear":
			GPIO.cleanup()
			return "GPIO cleanup()"


