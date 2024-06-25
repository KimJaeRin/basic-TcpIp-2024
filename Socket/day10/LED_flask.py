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
	return "LED ON"
			  GPIO.output(led, False)

if __name__ == "__main__":
	app.run(host="0.0.0.0")
