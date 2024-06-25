import RPi.GPIO as GPIO
import time

buzzer_pin = 13 
trig_pin = 27
echo_pin = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(buzzer_pin, GPIO.OUT)
GPIO.setup(trig_pin, GPIO.OUT)
GPIO.setup(echo_pin, GPIO.IN)

def play_buzzer(frequency):
    pwm = GPIO.PWM(buzzer_pin, frequency)
    pwm.start(50)
    time.sleep(0.1)
    pwm.stop()

# 거리 측정 함수
def measure_distance():
    GPIO.output(trig_pin, True)
    time.sleep(0.00001)
    GPIO.output(trig_pin, False)

    while GPIO.input(echo_pin) == 0:
        pulse_start = time.time()

    while GPIO.input(echo_pin) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150
    return distance

try:
    while True:
        distance = measure_distance()
        print(f"Distance: {distance:.2f} cm")

        # 거리에 따라 부저 소리 조절
        if distance < 10:
            play_buzzer(3000)
        elif distance < 20:
            play_buzzer(2000)
        elif distance < 30:
            play_buzzer(1000)
        elif distance < 40:
            play_buzzer(500)
        else:
            play_buzzer(100)

        time.sleep(0.1)  # 0.1초 간격으로 반복

except KeyboardInterrupt:
    GPIO.cleanup()
    print("Program terminated.")
