/**
   @name Button
   @desc A debounced button

   @package Arduino Basics
   @author Michael <michael@zenbox.de>
   @since 2017/01/03
   @version v1.0.0
   @copyright (c) 2017 Michael Reichart
   @license MIT License <http://opensource.org/licenses/MIT>
*/

const byte BUTTON_PIN = 2;
boolean buttonState  = LOW;
boolean oldState     = LOW;
boolean currentState = LOW;

unsigned long currentMillis = 0;
unsigned long oldMillis = 0;
unsigned long passedMillis = 0;
unsigned int debounceTime = 20;

void setup() {
  /**
     @name setup
     @desc the setup function runs once when the board is started by
           pressing the reset button or empower the board.
           While setting up, pins and the Serial port can be configured.
  */

  //setting up the serial port
  Serial.begin(115200);

  // setting up the button pin
  pinMode(BUTTON_PIN, INPUT);

  // store the starting time as current time
  currentMillis = millis();
}

void loop() {
  /**
      @name loop
      @desc the loop function runs over and over again forever. It will
            runs the process while, the board has power.
  */

  // read the button state, is it pressed or not?
  currentState = digitalRead(BUTTON_PIN);

  // if the current state has changed since the last processor cycle
  if (currentState != oldState) {
    // store the current time value
    currentMillis = millis();

    // calculate the time passed since the last button state change
    passedMillis = currentMillis - oldMillis;

    // change the btton state value only if it is not a debounce effect
    if (passedMillis > debounceTime) {
      buttonState = !buttonState;
      Serial.print(buttonState);
      Serial.print(" passed ");
      Serial.print(passedMillis);
      Serial.print(" millis, button state has changed! ");
      Serial.println();
    }

    // keep state and time as old values
    oldState = currentState;
    oldMillis = currentMillis;
  }
}
