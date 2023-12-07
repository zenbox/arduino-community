/*
    My First Own Blick
    by Michael
    ...
*/

// Declaration of variables
const int ledPin = 9;
int ledValue;

const int btnPin = 5;
boolean btnState;

const int potPin = A1;
int potValue;

int delayTime = 20;


// put your setup code here, to run once:
void setup() {
  Serial.begin(115200);


  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  // Read the state while starting
  btnState = digitalRead(btnPin);

  // Read the potentiometer value while starting
  potValue = analogRead(potPin);
}

// put your main code here, to run repeatedly:
void loop() {
  // Read the button
  btnState = digitalRead(btnPin);

  // Read the potentiometer
  potValue = analogRead(potPin);
  Serial.println(potValue);


  // Set the potentiometer value as led value
  // pwm -> 0 - 255!
  // Recalculate
  ledValue = map(potValue, 0, 1023, 0, 255);


  if ( btnState == HIGH ) {
    //digitalWrite(ledPin, HIGH);
    analogWrite(ledPin, ledValue);
    delay(delayTime);
  }
  else {
    digitalWrite(ledPin, LOW);
    delay(delayTime);
  }

}
