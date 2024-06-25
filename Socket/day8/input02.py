import RPi.GPIO as GPIO

# GPIO 핀 번호 설정
LED_PIN = 21

# GPIO 핀 번호 모드 설정
GPIO.setmode(GPIO.BCM)

# LED 핀 초기화
GPIO.setup(LED_PIN, GPIO.OUT)

try:
    while True:
        # 사용자로부터 키보드 입력 받기
        input_char = input("Press 'p' to turn LED on, 'o' to turn LED off: ")

        if input_char == 'p':
            GPIO.output(LED_PIN, GPIO.HIGH)  # LED 켜기
            print("LED turned ON")
        elif input_char == 'o':
            GPIO.output(LED_PIN, GPIO.LOW)  # LED 끄기
            print("LED turned OFF")
        else:
            print("Invalid input. Press 'p' or 'o'.")

except KeyboardInterrupt:
    GPIO.cleanup()
