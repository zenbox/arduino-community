/**
   Lichtschwert by Mathis
   @version 1.0.0
   @since 2018-11-01
   @author Mathis

   AT Tiny:
   Reset -| U |- 5V
   A3, 3 -|   |- 2, A1
   A2, 4 -|   |- 1 (PWM)
   GND   -|   |- 0 (PWM)
*/
// for Tiny
//int ledPin1 = 0;
//int ledPin2 = 1;
//int ledPin3 = 2;
//int buttonPin = 3;
//int powbuttonPin = 4;

// for UNO
int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int buttonPin = 5;
int powbuttonPin = 6;

int buttonState = 0;
int state = 0;
int powbuttonState = 0;
int power = 0;

int delayZeit = 150;


void setup() {
  Serial.begin(9600);
  Serial.println("started");

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(powbuttonPin, INPUT);
}

void loop() {
  // - - - - - - - - - -
  // read button
  buttonState = digitalRead(buttonPin);
  powbuttonState = digitalRead(powbuttonPin);

  // - - - - - - - - - -
  // color button states
  if (buttonState == HIGH) {
    state = state + 1;

    if (state > 2) {
      state = 0;
    }

    Serial.print("state is ");
    Serial.print(state);
    Serial.println();
  }

  // - - - - - - - - - -
  // power button states
  if (powbuttonState == HIGH ) {
    if (power == 0) {
      power = 1;
    } else {
      power = 0;
    }

    Serial.print("power is ");
    Serial.print(power);
    Serial.println();

  }

  // Control: was passiert ...

  if (power == 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    delay(delayZeit);

  } else {
    switch (state) {
      case 0:
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        break;

      case 1:
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
        break;

      case 2:
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, HIGH);
        break;
    }
    delay(delayZeit);

  }
}
