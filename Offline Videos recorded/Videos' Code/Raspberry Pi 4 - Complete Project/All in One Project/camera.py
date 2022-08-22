
from picamera import PiCamera  
import time 


def cam():    
    camera = PiCamera()
    #camera.rotation = 90
    camera.start_preview()
    time.sleep(3)
    camera.capture('/home/pi/Desktop/imgs/image.jpg')
    camera.stop_preview()

