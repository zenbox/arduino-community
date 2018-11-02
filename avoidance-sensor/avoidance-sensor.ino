/**
   Avoidance Sensor
   @since 2018-11-02
   @author Michael
   @version 1.0.0
*/

// declaration
int count = 0;
int ledPin = 8;
int sensorPin = 9;
int sensorValue;

void setup() {
  Serial.begin (9600);

  pinMode (ledPin, OUTPUT);
  pinMode (sensorPin, INPUT);
}

void loop()
{
  sensorValue = digitalRead(sensorPin);

  if (sensorValue == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.print (count++);
  Serial.print (" Sensor: ");
  Serial.println (digitalRead(9)); //print the sensor output
  delay (500); //wait half a second
}
