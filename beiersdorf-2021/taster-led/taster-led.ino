/*
   Script to control a led via button ...
   v1.0.0
   @author Michael
*/

// 1. Declaration of variables
int ledPin = 11; // numbers
int buttonPin = 5;
boolean buttonState; // true/false values


// 2. Setup while board starts
void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

    buttonState = digitalRead(buttonPin);

}

// 3. Code runs while board has current
//    16 000 times per second!
void loop() {

  buttonState = digitalRead(buttonPin);

  // Condition!
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
