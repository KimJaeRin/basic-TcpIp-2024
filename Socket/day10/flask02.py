import RPi.GPIO as GPIO
from flask import Flask

RED_pin = 17

app = Flask(__name__)

@app.route("/")
def fhello():
	return "Hello World"

if __name__ == "__main__":
	app.run(host="0.0.0.0")
