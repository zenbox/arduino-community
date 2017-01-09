#include <Arduino.h>

/**
 * @name Interupts with Arduino Uno
 * @desc How to do multiple things at the same time.
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/05
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

/**
 * @desc the interrupt pin at Arduino Uno
 *       Other borads have other pins for interrupts
 */
const int INTERRUPT_PIN = 2;

/**
 * @desc a state to be changed by interrupt
 */
volatile bool aState = LOW;

// declare a pin for the onboard led
const byte PIN = 13;

void blonk () {
	aState = !aState;
}

void setup() {
	// init a serial port
	Serial.begin(9600);
	Serial.print("Everything seems fine ...");

	// init the led pin
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);

	/**
	 * @desc adding an interrupt
	 */
	attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), blonk, CHANGE);
	pinMode(INTERRUPT_PIN, INPUT);
}

void loop() {
	/**
	 * @desc starting the interrupts
	 */
	interrupts();

	// blink
	digitalWrite(PIN, HIGH);
	delay(500);
	digitalWrite(PIN, LOW);
	delay(500);
}
