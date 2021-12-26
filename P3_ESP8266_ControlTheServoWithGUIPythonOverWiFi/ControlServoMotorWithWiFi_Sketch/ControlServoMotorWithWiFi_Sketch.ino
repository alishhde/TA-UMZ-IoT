#include "Servo.h"
#include <ESP8266WiFi.h>

int port = 8888;
WiFiServer server(port);

const char *ssid = "Aliiii";
const char *password = "9012117316";
int reaad;

Servo myservo;
//int servo_pin = 9;  // for Arduino microcontroller
//int servo_pin = 4;  // for ESP32 microcontroller
int servo_pin = D1;  // for ESP8266 microcontroller
int angle = 0;  
 
void setup() 
{ 
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  server.begin();
  Serial.print("Open telnet and connect to IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
  
  myservo.attach(servo_pin);
} 
  
void loop() 
{ 
  WiFiClient client = server.available();

  while (client.connected()){
    if (client.available() > 0 ){
      reaad = client.read();
      if (reaad == 79){
        myservo.write(78);
      }
      if (reaad == 67){
        myservo.write(8);
      }
    }
  }
}
