/**
   @name Better Blink
   @desc First approach to write an arduino program

   @package Arduino Basics
   @author Michael <michael@zenbox.de>
   @since 2017/01/02
   @version v1.0.0
   @copyright (c) 2017 Michael Reichart
   @license MIT License <http://opensource.org/licenses/MIT>
*/
/**
 * @desc declare a constant value
 *       constant values will be set once in memory
 *       They will never change while proceesing the
 *       program. Constants use less memory than variables.
 *       Constants use UPPERCASE names by convention.
 */
const int PIN = 13;

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

  // initialize digital pin 13 as an output.
  // OUTPUT is a Arduino constant value
  pinMode(PIN, OUTPUT);
}

void loop() {
  /**
     @name loop
     @desc the loop function runs over and over again forever. It will
           runs the process while, the board has power.
  */
  Serial.println("loop!");
  
  digitalWrite(PIN, HIGH);
  delay(1000);
  digitalWrite(PIN, LOW);
  delay(1000);
}

