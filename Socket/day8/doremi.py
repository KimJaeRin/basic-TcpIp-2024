import RPi.GPIO as GPIO
import time

BUZZER_PIN = 13

frq = [262, 294, 330, 349, 392, 440, 494, 523]

# GPIO 핀 번호 모드 설정
GPIO.setmode(GPIO.BCM)

GPIO.setup(BUZZER_PIN, GPIO.OUT)
buzzer = GPIO.PWM(BUZZER_PIN, 100)

try:
    while True:
        input_char = input("input number (1-8): ")
        try:
            i = int(input_char) - 1
            if 0 <= i < len(frq):
                buzzer.start(50)
                buzzer.ChangeFrequency(frq[i])
                time.sleep(0.5) 
                buzzer.stop()
            else:
                print("1-8 입력")
        except ValueError:
            print(".")

except KeyboardInterrupt:
    GPIO.cleanup()
