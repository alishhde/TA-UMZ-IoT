const int PIRSensorOutPin = D6;    //PIR Sensor OUT Pin
#define LEDPin D7
#define BuzzerPin D5

 void setup() {
    Serial.begin(9600);
    pinMode(PIRSensorOutPin, INPUT);
    pinMode(LEDPin, OUTPUT);
    pinMode(BuzzerPin, OUTPUT);
 }
 void loop()
 {
    if (digitalRead(PIRSensorOutPin) == LOW)
    {
      
      Serial.println("Person detected!");    //Print to serial monitor
      digitalWrite(LEDPin, HIGH);
      
      tone(BuzzerPin, 523) ; //DO note 523 Hz
      delay (1000); 
      tone(BuzzerPin, 587) ; //RE note ...
      delay (1000); 
      tone(BuzzerPin, 659) ; //MI note ...
      delay (1000); 
      tone(BuzzerPin, 783) ; //FA note ...
      delay (1000); 
      tone(BuzzerPin, 880) ; //SOL note ...
      delay (1000); 
      tone(BuzzerPin, 987) ; //LA note ...
      delay (1000); 
      tone(BuzzerPin, 1046) ; // SI note ...
      delay (1000); 
    }
    else {
      digitalWrite(LEDPin, LOW);
      digitalWrite(BuzzerPin, LOW);
      }
 }
