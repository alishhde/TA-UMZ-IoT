import RPi.GPIO as GPIO
import time


def tou():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(17, GPIO.IN)         #Read output from PIR motion sensor
    pad_pin = 17

    pad = GPIO.input(17)


    already_pressed = False

    while True:
        pad = GPIO.input(17)
        
        if pad:
            print("pressed")