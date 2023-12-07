// defines pins numbers
const int stepPin = 5;
const int dirPin = 4;
const int enPin = 8;

volatile unsigned int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder

boolean stepperState = false;
int stepperX = 0;
int d = 800;

int potPin = A0;
int potValue;

void setup() {

  Serial.begin (9600);

  // Poti
  potValue = analogRead(potPin);

  // Rotary encoder
  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2
  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);

  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

}
void loop() {
  potValue = analogRead(potPin);
  d = map(potValue, 0, 1023, 300, 1200);

  // Rotary encoder counter
  if ( counter != temp ) {
    //  Serial.println (counter);
    temp = counter;
  }

  if (stepperState = false) {
    digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
    stepperState = true;
  }

//  if (stepperX < 100000) {
    // Stepper motor
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(d);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(d);
  //  stepperX++;
  //} else {

 // }

  //  digitalWrite(dirPin,LOW); //Changes the rotations direction
  //  // Makes 400 pulses for making two full cycle rotation
  //  for(int x = 0; x < 800; x++) {
  //    digitalWrite(stepPin,HIGH);
  //    delayMicroseconds(500);
  //    digitalWrite(stepPin,LOW);
  //    delayMicroseconds(500);
  //  }
  //  delay(1000);

}

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
