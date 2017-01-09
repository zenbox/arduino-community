#include <Arduino.h>
#include <Morse.h>

/**
 * @name writing a library
 * @desc How to write and use an own library.
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/05
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */


// declare a pin for the onboard led
const byte PIN = 13;

// a Morse instance
Morse morse(PIN);

void setup() {
	// init a serial port
	Serial.begin(9600);
	Serial.println("Everything seems fine ...");

	// init the led pin
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);
}


void loop() {

	morse.dot(); morse.dot(); morse.dot();
	morse.dash(); morse.dash(); morse.dash();
	morse.dot(); morse.dot(); morse.dot();
	delay(500);
}
