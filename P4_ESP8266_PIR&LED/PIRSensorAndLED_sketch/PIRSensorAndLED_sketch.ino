 const int PIRSensorOutPin = D5;    //PIR Sensor OUT Pin
 #define LEDPin D6
 
 void setup() {
    Serial.begin(9600);
    pinMode(PIRSensorOutPin, INPUT);
    pinMode(LEDPin, OUTPUT);
 }
 void loop()
 {
    if (digitalRead(PIRSensorOutPin) == LOW)
    {
      digitalWrite(LEDPin, HIGH);
      Serial.println("Person detected!");    //Print to serial monitor
    }
    else {
      digitalWrite(LEDPin, LOW);
      }
 }
