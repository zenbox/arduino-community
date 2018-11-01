
int ledPin1 = 0;
int ledPin2 = 1;
int ledPin3 = 2;
int buttonPin = 3;
int buttonState = 0;
int state = 0 ;
int hasChanged = 1;
int powbuttonPin = 4;
int powbuttonValue = 0;
int power = 0;
int on = 0;


void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(powbuttonPin, INPUT);


}

void loop() {

  if (power == 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);

  }
  buttonState = digitalRead(buttonPin);
  powbuttonValue = digitalRead(powbuttonPin);
  delay(150);

  if (powbuttonValue == 1 ) {
    if (on == 0) {
      power = power + 1;
      on = on + 1;
      delay(80);
    }
    else if (on == 1) {
      power = 0;
      on = 0;
    }
  }





  if (buttonState == HIGH) {
    state = state + 1;
  }

  if (state == 4) {
    state = 0;
  }


  if (power == 1) {
    switch (state) {
      case 0:
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        hasChanged = 0;

        break;

      case 1:
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
        hasChanged = 0;

        break;

      case 2:
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, HIGH);
        hasChanged = 1;

        break;
    }
  }
}



