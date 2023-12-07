// Comment: My first program

// 1: Declaration of variables
int buttonPin = 4;
boolean buttonState;

int ledPin = 9;
boolean ledState;

int potPin = A1;
int potValue;

// 2. Setup
void setup() {
  // put your setup code here, to run once:

  // Control the led initial state
  ledState = LOW;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Set the button pin to input
  // and read the initial button state
  pinMode(buttonPin, INPUT);
  buttonState = digitalRead(buttonPin);

  // Initial reading of the potentiometer
  potValue = analogRead(potPin);

  // Serial monitor
  Serial.begin(9600);

}



// 3. Process
void loop() {
  // put your main code here, to run repeatedly:
  //

  // Button controls the led
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    ledState = HIGH;
    delay(200);
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);

  // The potantiometer
  potValue = analogRead(potPin);
  Serial.println(potValue);

}
