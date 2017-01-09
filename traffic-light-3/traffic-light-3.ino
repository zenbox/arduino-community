/**
   @name Traffic light
   @desc Using functions.
         A traffic light with debounced button.
         cars have a green signal, until a pedestrian
         pushes the button. The button push starts the
         pedestrian light sequence.

   @package Arduino Basics
   @author Michael <michael@zenbox.de>
   @since 2017/01/03
   @version v1.0.0
   @copyright (c) 2017 Michael Reichart
   @license MIT License <http://opensource.org/licenses/MIT>
*/

// traffic light pins
const byte NUMBER_OF_TRAFFIC_LIGHTS = 5;
byte trafficLightPins[NUMBER_OF_TRAFFIC_LIGHTS] = {12, 11, 10, 9, 8};

// traffic light states
// car: red, red/yellow, green, yellow, red
// pedestrian: green, red
const byte NUMBER_OF_TRAFFIC_LIGHT_STATES = 6;                // schaltet auf Rot
byte redForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]          = {LOW,  LOW,  HIGH, HIGH, HIGH, HIGH };
byte yellowForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]       = {LOW,  HIGH, LOW,  LOW,  LOW,  HIGH };
byte greenForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]        = {HIGH, LOW,  LOW,  LOW,  LOW,  LOW  };
byte redForPedestrianStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]   = {HIGH, HIGH, HIGH, LOW,  HIGH, HIGH };
byte greenForPedestrianStates[NUMBER_OF_TRAFFIC_LIGHT_STATES] = {LOW,  LOW,  LOW,  HIGH, LOW,  LOW  };
// the button pins and init states values
const byte BUTTON_PIN = 2;
boolean buttonState  = LOW;
boolean oldButtonState     = LOW;
boolean currentButtonState = LOW;

// button and debounce time
unsigned long currentButtonMillis = 0;
unsigned long oldButtonMillis = 0;
unsigned long passedButtonMillis = 0;
unsigned int debounceTime = 20;

void setup() {
  /**
     @name setup
     @desc the setup function runs once when the board is started by
           pressing the reset button or empower the board.
           While setting up, pins and the Serial port can be configured.
  */

  // setting up the serial port
  Serial.begin(115200);

  // setting up the button pin
  pinMode(BUTTON_PIN, INPUT);

  // initialize all pins.
  // iterate over the pins to set them as output
  for (byte i = 0; i < NUMBER_OF_TRAFFIC_LIGHTS; i += 1) {
    pinMode(trafficLightPins[i], OUTPUT);
  }

  // start the car sequence function for "car has green"
  startCarSequence();

  // store the starting time as current time
  currentButtonMillis = millis();
}

void loop() {
  /**
      @name loop
      @desc the loop function runs over and over again forever. It will
            runs the process while, the board has power.
  */

  // read the button state, is it pressed or not?
  currentButtonState = digitalRead(BUTTON_PIN);

  // if the current state has changed since the last processor cycle
  if (currentButtonState != oldButtonState) {
    currentButtonMillis = millis();
    passedButtonMillis = currentButtonMillis - oldButtonMillis;

    // calculate the time passed since the last button state change
    if (passedButtonMillis > debounceTime) {
      buttonState = !buttonState;

      // start sequences depending on the button state value
      if (buttonState == true) {
        startPedestrianSequence();
      } else {
        startCarSequence();
      }
    }

    // keep state and time as old values
    oldButtonState  = currentButtonState;
    oldButtonMillis = currentButtonMillis;
  }
}

void startPedestrianSequence() {
  /**
     @name startPedestrianSequence
     @desc The traffic light sequence
           to be used if the button is pressed.
  */
  Serial.print("startPedestrianSequence");
  Serial.println();

  /* @desc looping through the traffic light states.
           and use them almost generecly as LOW/HIGH value
           within the different traffic light pins.
  */
  for (byte i = 0; i < NUMBER_OF_TRAFFIC_LIGHT_STATES; i += 1) {
    digitalWrite(trafficLightPins[0], redForCarStates[i]);
    digitalWrite(trafficLightPins[1], yellowForCarStates[i]);
    digitalWrite(trafficLightPins[2], greenForCarStates[i]);
    digitalWrite(trafficLightPins[3], redForPedestrianStates[i]);
    digitalWrite(trafficLightPins[4], greenForPedestrianStates[i]);

    delay(100);
  }

}

void startCarSequence() {
  /**
     @name startCarSequence
     @desc The traffic light states for "car light is green".
           It will be kept, while the button is not pressed.
  */
  digitalWrite(trafficLightPins[0], redForCarStates[0]);
  digitalWrite(trafficLightPins[1], yellowForCarStates[0]);
  digitalWrite(trafficLightPins[2], greenForCarStates[0]);
  digitalWrite(trafficLightPins[3], redForPedestrianStates[0]);
  digitalWrite(trafficLightPins[4], greenForPedestrianStates[0]);
}
