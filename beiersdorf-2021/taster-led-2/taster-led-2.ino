/*
   Script to control a led via button ...
   v1.0.0
   @author Michael
*/

// 1. Declaration of variables
int ledPin = 11; // numbers
int buttonPin = 5;

boolean buttonState; // true/false values
boolean ledState;


// 2. Setup while board starts
void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  buttonState = digitalRead(buttonPin);
  ledState = LOW;

}

// 3. Code runs while board has current
//    16 000 times per second!
// 200ms 16 000/5 = 3 300 
void loop() {

  digitalWrite(ledPin, ledState);
  buttonState = digitalRead(buttonPin);

  // Condition!
  if (buttonState == HIGH) {

  // ! (not) is a logical operator, that inverses a boolean value
  ledState = !ledState;
  delay(100);
/*
    if ( ledState == HIGH) {
      ledState = LOW;
    } else {
      ledState = HIGH;
    }
*/

  } else {}



}
