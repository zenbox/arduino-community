/**
   Lichtschwert by Linus
   @version 1.0.0
   @since 2018-11-01
   @author Linus

   AT Tiny:
   Reset -| U |- 5V
   A3, 3 -|   |- 2, A1
   A2, 4 -|   |- 1 (PWM)
   GND   -|   |- 0 (PWM)
*/

int ledR = 0;
int ledG = 1;
int ledB = 2;
int button = 3;
int buttonstate = 0;
int state = 1;
int power = 0;
int powerbutton = 4;
int powerbuttonstate = 0;
int active = 0;
int delayZeit = 200;
int on = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("started");

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(button, INPUT);
  pinMode(powerbutton, INPUT);
  Serial.println("Pinmodes set");
}

void loop() {
  buttonstate = digitalRead(button);
  powerbuttonstate = digitalRead(powerbutton);

  // - - - - - - - - - -
  // color button
  if (buttonstate == HIGH) {
    state = state + 1;

    if (state > 4) {
      state = 1;
    }
    delay(delayZeit);

    Serial.print("state is ");
    Serial.print(state);
    Serial.println();
  }


  // - - - - - - - - - -
  // power button
  if (powerbuttonstate == HIGH ) {

    if (power == 0) {
      power = 1;
    }
    else if (power == 1) {
      power = 0;
    }

    Serial.print("power is ");
    Serial.print(power);
    Serial.println();

    delay(delayZeit);
  }

  if (power == 0) {
    analogWrite(ledR, LOW);
    analogWrite(ledG, LOW);
    analogWrite(ledB, LOW);
    delay(delayZeit);
  } else {
    switch (state) {
      case 1:
        digitalWrite(ledR, HIGH);
        digitalWrite(ledG, LOW);
        digitalWrite(ledB, LOW);
        break;
      case 2:
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, HIGH);
        digitalWrite(ledB, LOW);
        break;
      case 3:
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);
        digitalWrite(ledB, HIGH);
        break;
      case 4:
        analogWrite(ledR, 255);
        analogWrite(ledG, 15);
        digitalWrite(ledB, LOW);
        break;
    }
  }
}
