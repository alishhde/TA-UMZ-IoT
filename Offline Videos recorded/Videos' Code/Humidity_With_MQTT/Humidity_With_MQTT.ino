#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker

// Code for the ESP32
//#include "WiFi.h" // Enables the ESP32 to connect to the local network (via WiFi)
//#define DHTPIN 4  // Pin connected to the DHT sensor

// Code for the ESP8266
#include "ESP8266WiFi.h"  // Enables the ESP8266 to connect to th8e local network (via WiFi)
#define DHTPIN D3         // Pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// WiFi
char* ssid = "HONOR";                 // Your personal network SSID
char* wifi_password = "f7690046f77f"; // Your personal network password

// MQTT
const char* mqtt_server = "192.168.43.16";  // IP of the MQTT broker
const char* humidity_topic = "home/livingroom/humidity";
const char* mqtt_username = "admin"; // MQTT username
const char* mqtt_password = "admin"; // MQTT password
const char* clientID = "client_livingroom"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 


// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT(){
  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  while (!client.connect(clientID, mqtt_username, mqtt_password)){
    if (client.connect(clientID, mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT Broker!");
    }
    else {
      Serial.println("Connection to MQTT Broker failed...");
      delay(800);
    }
  }
}


void setup() {
  Serial.begin(9600);
  dht.begin();


//################## WiFi ###################
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("########################");
//################## WiFi ###################
}

void loop() {
  connect_MQTT();
  Serial.setTimeout(2000);
  
  float h = dht.readHumidity();
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
  
  // MQTT can only transmit strings
  String hs="Hum: "+String((float)h)+" % ";

  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  if (client.publish(humidity_topic, String(h).c_str())) {
    Serial.print("Humidity sent to broker with ");
    Serial.print(mqtt_server);
    Serial.println(" IP!");
    Serial.println("########################");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Humidity failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(humidity_topic, String(h).c_str());
  }
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*10);       // print new values every 1 Minute
}
