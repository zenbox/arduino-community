// Tastensteuerung einer LED

int buttonPin = 5;
int buttonState;

int ledPin = 11;


void setup() {
  // Button liefert Strom als Eingabe!
  pinMode(buttonPin, INPUT);
  buttonState = digitalRead(buttonPin);

  // Led nimmt Strom als Ausgabe!
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  digitalWrite(ledPin, buttonState);

}
