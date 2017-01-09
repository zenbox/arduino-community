/**
   @name Traffic Light
   @desc a simple traffic light program

   @package Arduino Basics
   @author Michael <michael@zenbox.de>
   @since 2017/01/02
   @version v1.0.0
   @copyright (c) 2017 Michael Reichart
   @license MIT License <http://opensource.org/licenses/MIT>
*/
/**
   @desc declare a constant value
         constant values will be set once in memory
         They will never change while proceesing the
         program. Constants use less memory than variables.
         Constants use UPPERCASE names by convention.
*/
const byte CAR_RED = 12;
const byte CAR_YELLOW = 11;
const byte CAR_GREEN = 10;
const byte PEDESTRIAN_RED = 9;
const byte PEDESTRIAN_GREEN = 8;
const byte BUTTON = 2;

void setup() {
  /**
     @name setup
     @desc the setup function runs once when the board is started by
           pressing the reset button or empower the board.
           While setting up, pins and the Serial port can be configured.
  */

  // setting up the serial port
  // 115200 is the baudrate
  Serial.begin(115200);

  // output a hello
  Serial.println("Hello");

  // initialize all pins.
  // OUTPUT is a Arduino constant value
  pinMode(CAR_RED, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(PEDESTRIAN_RED, OUTPUT);
  pinMode(PEDESTRIAN_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
  /**
     @name loop
     @desc the loop function runs over and over again forever. It will
           runs the process while, the board has power.
  */
  Serial.println("loop!");

  // car is red
  digitalWrite(CAR_RED, HIGH);
  digitalWrite(CAR_YELLOW, LOW);
  digitalWrite(CAR_GREEN, LOW);
  // pedestrian is green
  digitalWrite(PEDESTRIAN_RED, LOW);
  digitalWrite(PEDESTRIAN_GREEN, HIGH);
  delay(1000);

  // car starts to green
  digitalWrite(CAR_RED, HIGH);
  digitalWrite(CAR_YELLOW, HIGH);
  digitalWrite(CAR_GREEN, LOW);
  // pedestrian is red
  digitalWrite(PEDESTRIAN_RED, HIGH);
  digitalWrite(PEDESTRIAN_GREEN, LOW);
  delay(1000);

  // car gets green
  digitalWrite(CAR_RED, LOW);
  digitalWrite(CAR_YELLOW, LOW);
  digitalWrite(CAR_GREEN, LOW);
  // pedestrian is red
  digitalWrite(PEDESTRIAN_RED, HIGH);
  digitalWrite(PEDESTRIAN_GREEN, LOW);
  delay(1000);

  // car gets yellow
  digitalWrite(CAR_RED, LOW);
  digitalWrite(CAR_YELLOW, HIGH);
  digitalWrite(CAR_GREEN, LOW);
  // pedestrian is red
  digitalWrite(PEDESTRIAN_RED, HIGH);
  digitalWrite(PEDESTRIAN_GREEN, LOW);
  delay(1000);
}

