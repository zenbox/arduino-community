/**
  @name Traffic Light
  @desc Using array as data lists, and for-loops with
        constant typed for-loop conditions to build a
        smart, self-configuring process.

  @package Arduino Basics
  @author Michael <michael@zenbox.de>
  @since 2017/01/02
  @version v1.0.0
  @copyright (c) 2017 Michael Reichart
  @license MIT License <http://opensource.org/licenses/MIT>
*/
/**
  @desc build an array for the light pins
        pins 12,11,10 are car light pins red, yellow, green
        pins 9, 8 are pedestrian lights red, green
*/

// traffic light pins
const byte NUMBER_OF_TRAFFIC_LIGHTS = 5;
byte trafficLightPins[NUMBER_OF_TRAFFIC_LIGHTS] = {12, 11, 10, 9, 8};

// traffic light states
// car: red, red/yellow, green, yellow, red
// pedestrian: green, red
const byte NUMBER_OF_TRAFFIC_LIGHT_STATES = 7;
byte redForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]          = {HIGH, HIGH, LOW,  LOW,  HIGH, HIGH, HIGH};
byte yellowForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]       = {LOW,  HIGH, LOW,  HIGH, LOW,  LOW,  LOW };
byte greenForCarStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]        = {LOW,  LOW,  HIGH, LOW,  LOW,  LOW,  LOW };
byte redForPedestrianStates[NUMBER_OF_TRAFFIC_LIGHT_STATES]   = {HIGH, HIGH, HIGH, HIGH, HIGH, LOW,  HIGH};
byte greenForPedestrianStates[NUMBER_OF_TRAFFIC_LIGHT_STATES] = {LOW,  LOW,  LOW,  LOW,  LOW,  HIGH, LOW };

// the button pin (a digital pin)
const byte BUTTON = 2;

void setup() {
  /**
     @name setup
     @desc the setup function runs once when the board is started by
           pressing the reset button or empower the board.
           While setting up, pins and the Serial port can be configured.
  */

  /* @desc setting up the serial port
           115200 is the baudrate
  */
  Serial.begin(115200);

  /* @desc Initialize all pins.
           loop over the pins to set them as output.
           the condition NUMBER_OF_TRAFFIC_LIGHTS is a constant,
           configuredin the declaration bloch at the beginning.
  */
  for (byte i = 0; i < NUMBER_OF_TRAFFIC_LIGHTS; i += 1) {
    pinMode(trafficLightPins[i], OUTPUT);
  }

  pinMode(BUTTON, INPUT);
}

void loop() {
  /**
     @name loop
     @desc the loop function runs over and over again forever. It will
           runs the process while, the board has power.
  */

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

    delay(1000);
  }
}

