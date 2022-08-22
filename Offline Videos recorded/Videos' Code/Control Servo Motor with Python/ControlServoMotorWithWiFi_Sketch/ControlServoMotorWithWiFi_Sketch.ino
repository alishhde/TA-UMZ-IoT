#include "Servo.h"
#include <ESP8266WiFi.h>

const char *ssid = "Ali3";
const char *password = "aaaaaaaa";
int reaad;

int port = 8888;
WiFiServer server(port); // creating a server object, defining the port which server is listening

Servo myservo; // Creating object named myservo by the Servo class
int servo_pin = D1;  // for ESP8266 microcontroller
int angle = 0;  

void setup() 
{ 
  Serial.begin(9600);
  
  WiFi.begin(ssid, password); // Connecting to the existing network (local WiFi)
  Serial.println("Connecting to WiFi..");

  /* 
  WL_CONNECTED: assigned when connected to a Wi-Fi network
  WL_NO_SHIELD: assigned when no Wi-Fi shield is present
  WL_IDLE_STATUS: a temporary status assigned when WiFi.begin() is called and remains active until the number of attempts expires (resulting in WL_CONNECT_FAILED) or a connection is established (resulting in WL_CONNECTED)
  WL_NO_SSID_AVAIL: assigned when no SSID are available
  WL_SCAN_COMPLETED: assigned when the scan networks is completed
  WL_CONNECT_FAILED: assigned when the connection fails for all the attempts
  WL_CONNECTION_LOST: assigned when the connection is lost
  WL_DISCONNECTED: assigned when disconnected from a network  
  */
  
  while (WiFi.status() != WL_CONNECTED) { // checking WiFi is connected to network or not
    delay(500);
    Serial.print(".");
    }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  server.begin();
  Serial.print("Open telnet and connect to IP: ");
  Serial.print(WiFi.localIP()); // WiFi.localIP() returns us our IP address
  Serial.print(" on port ");
  Serial.println(port);
  
  myservo.attach(servo_pin); // servo attach pin
} 
  
void loop() 
{ 
  WiFiClient client = server.available();
  Serial.println("No Client..");
  while (client.connected()){
    Serial.println("Client Connected but no data sends..");
    if (client.available()){
      Serial.println("Client is available.\n");
      reaad = client.read();
      Serial.println(reaad);
      if (reaad == 70 ){
        Serial.println("Going Forward");
        for(angle = 0; angle < 180; angle += 1)
            {                          
              myservo.write(angle);
              delay(12);                       
            }
      }
      
      if (reaad == 66 ){
         Serial.println("Going Backward");
         for(angle = 180; angle>=1; angle-=5)
            {                                
              myservo.write(angle);
              delay(25);                       
            }
      }
    }
    delay(1000);
  }
  delay(1000);
}
