#include "Servo.h"

//int servo_pin = 9;  // for Arduino microcontroller
int servo_pin = D1;  // for ESP8266 microcontroller
//int servo_pin = 4;  // for ESP32 microcontroller

Servo myservo;
int angle = 0;  
 
void setup() 
{ 
  myservo.attach(servo_pin);
} 
  
void loop() 
{ // move from 0 to 180 degrees with a positive angle of 1
  for(angle = 0; angle < 360; angle += 1)
  {                          
    myservo.write(angle);
    delay(25);                       
  } 

  delay(1000);
  
  // move from 180 to 0 degrees with a negative angle of 5
  for(angle = 180; angle>=1; angle-=5)
  {                                
    myservo.write(angle);
//    delay(5);                       
  } 

    delay(1000);
}
