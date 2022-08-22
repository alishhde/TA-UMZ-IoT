#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

#define WIFI_AP "Ali3"
#define WIFI_PASSWORD "aaaaaaaa"
#define TOKEN "JxE8CUb1tAGGHowbbz1q"

char thingsboardServer[] = "platform.smbapp.ir";

WiFiClient wifiClient;
ThingsBoard tb(wifiClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup()
{
  Serial.begin(115200);
  delay(10);
  InitWiFi();
  lastSend = 0;
}

void loop()
{
  if ( !tb.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    getAndSendMQ4Data();
    lastSend = millis();
  }

  tb.loop();
}

void getAndSendMQ4Data()
{
  float sensorVoltage; 
  float sensorValue;
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*5.0;
 
  Serial.print("Sensor Voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");

  Serial.print("Sensor Value = ");
  Serial.println(sensorValue);

  Serial.println("Sending to ThingsBoard..");

  tb.sendTelemetryInt("Sensor Value", sensorValue);
  tb.sendTelemetryFloat("Sensor Voltage", sensorVoltage);
  Serial.println("Sent!");
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}


void reconnect() {
  // Loop until we're reconnected
  while (!tb.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      // Code to connect to WiFi
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }

    // Code to connect to Thingsboard
    Serial.print("Connecting to ThingsBoard node ...");
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
