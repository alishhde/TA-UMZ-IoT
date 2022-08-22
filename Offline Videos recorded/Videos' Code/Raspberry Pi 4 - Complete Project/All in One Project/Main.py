import camera
import touch
import Ultrasonic
import DHT11
import Buzzer
import RPi.GPIO as GPIO
from time import sleep



GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

def initial(on_start):
    if on_start:
        led=12
        GPIO.setup(led,GPIO.OUT)
        GPIO.output(led,GPIO.HIGH)
        on_start = False
        sleep(3)
        GPIO.output(led,GPIO.LOW)
    Buzzer.Buzz()

on_start = True
initial(on_start)



distance = Ultrasonic.ultra()
if distance > 20:
    pass
elif distance > 10 :









