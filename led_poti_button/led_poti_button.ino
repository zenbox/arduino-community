/**
   @desc Better blink does a better blink ...
         i.e. better variables, better structure ...
   @package Arduino Basics
   @module betterBlink
   @author Michael
   @version 1.0.0
   @since 1.0.0 (2022-11-14)
   @copyright (c) 2022 GFU Cyrus AG, All rights reserved
   @license MIT License <https://opensource.org/licenses/MIT>
*/

// Common variables, general scope:
const byte PIN_LED = 3;
const byte PIN_BUTTON = 2; // Interrupt port
const byte PIN_POTI = A1;

unsigned int valuePoti;

volatile bool currentButtonState;


/**
   @desc ... if needed.
   @param int myVariable delivers the poti value
   @return void
*/
void setup() {
  // Use serial monitor or plotter
  Serial.begin(115200);
  Serial.print("Button Poti runs ...");
  Serial.println("");

  // Inital led pin as output
  // OUTPUT is an Arduino constant value
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), myInterruptFunction, FALLING);

  // read board states
  valuePoti = analogRead(PIN_POTI);
}

/**
   @desc put your main code here, to run repeatedly
   @returns void
*/
void loop() {

  valuePoti = map(analogRead(PIN_POTI), 0,1023, 0,255);
  
  analogWrite(PIN_LED, valuePoti);

  Serial.println(valuePoti);
  delay(10);

  if (currentButtonState == true) {
    digitalWrite(PIN_LED, HIGH);
    // Digital debounce!
    delay(10);
  } else {
    digitalWrite(PIN_LED, LOW);
    // Debounce!
    delay(10);
  }


}

void myInterruptFunction () {
  currentButtonState = !currentButtonState;
}
