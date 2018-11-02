/**
   Avoidance Sensor
   @since 2018-11-02
   @author Michael
   @version 1.0.0
*/

// declaration
int count = 0;
int ledYellowPin = 7;
int ledRedPin = 8;
int sensorPin = 9;
int sensorValue;

void setup() {
  Serial.begin (9600);

  pinMode (ledYellowPin, OUTPUT);
  pinMode (ledRedPin, OUTPUT);
  pinMode (sensorPin, INPUT);
}

void loop()
{
  sensorValue = digitalRead(sensorPin);

  if (sensorValue == HIGH) {
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
  } else {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, HIGH);
  }

  //Serial.print (count++);
  //Serial.print (" Sensor: ");
  //Serial.println (digitalRead(9)); //print the sensor output
  //delay (500); //wait half a second
}
