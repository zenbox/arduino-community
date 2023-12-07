#define BUTTON 6
#define LED 2

int buttonState  = 0;
int ledState = LOW;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  buttonState = digitalRead(BUTTON);
}

void loop() {
  // read button
  buttonState = digitalRead(BUTTON);

  // set led
  // ledState = !buttonState;

  // toogle led
  if (buttonState == LOW) {
    ledState = !ledState;
    digitalWrite(LED, ledState);
    delay(200);
    while (!digitalRead(BUTTON)) delay(100);
  }


}
