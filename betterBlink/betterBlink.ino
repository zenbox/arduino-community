/**
 * @desc Better blink does a better blink ...
 *       i.e. better variables, better structure ...
 * @package Arduino Basics
 * @module betterBlink
 * @author Michael
 * @version 1.0.0
 * @since 1.0.0 (2022-11-14)
 * @copyright (c) 2022 GFU Cyrus AG, All rights reserved
 * @license MIT License <https://opensource.org/licenses/MIT>
 */

// Common variables, general scope:
const byte PIN = 6;

/**
 * @desc ... if needed.
 * @param int myVariable delivers the poti value
 * @return void
 */
void setup() {
  // Inital value for pin 13 as output
  // OUTPUT is an Arduino constant value
  pinMode(PIN, OUTPUT);
}

/**
 * @desc put your main code here, to run repeatedly
 * @returns void
 */
void loop() {
  digitalWrite(PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(PIN, LOW);
  delayMicroseconds(9000);
}
