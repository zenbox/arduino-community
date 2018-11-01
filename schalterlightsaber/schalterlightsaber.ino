int switchPin = 5;
int switchValue = digitalRead(switchPin);







void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  switchValue = digitalRead(switchPin);
  if (switchValue == HIGH) {
    Serial.println("juhu");
  } else {
    Serial.println("buhu");
  }
}
