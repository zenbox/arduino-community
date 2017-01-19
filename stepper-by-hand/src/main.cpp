#include <Arduino.h>

/**
 * @name Stepper by hand
 * @desc How to drive a stepper motor without library.
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/05
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

/**
 *  @desc Stepper 28BYJ-48 without library.
 *        Motor pins: 1-Blue, 2-Pink, 3-Yellow, 4-Orange
 *        Red - VCC. The motor shield pins IN1, IN2, IN3, IN4
 *        are for the electromagnetic coils in the stepper.
 *        The motorshield power supply and ground can be connected
 *        to the arduino power and ground, for testing.
 *        Test some speed limitations. It depends on the
 *        used power supply, how fast a stepper can be driven.
 *
 * @link https://grahamwideman.wikispaces.com/Motors-+28BYJ-48+Stepper+motor+notes
 */
const byte NUM_STEPPER_PINS = 4;
int stepperPins[NUM_STEPPER_PINS] = {7,6,5,4};
boolean stepperPinState = false;
int speedMax = 120;
int speedMin = 4000;
int speed = 0;

/**
 * @desc the data sequence for the electromagnetic coils.
 *       We need 8 steps for one full rotation. The steps
 *       are easily binary noted.
 *
 */
// Anzahl der Schritte für einen Umdrehungszyklus
const int NUM_DATA = 8;
byte dataLeft[NUM_DATA];

// declare a pin for the onboard led
const byte PIN = 13;

void setup() {
	// init a serial port
	Serial.begin(9600);
	Serial.println("Everything seems fine ...");

	// init the led pin
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);

	pinMode(PIN, LOW);


	/**
	 * @desc init the stepper pins
	 */
	for ( byte i = 0; i < NUM_STEPPER_PINS; i++) {
		pinMode(stepperPins[i], OUTPUT );
	}
	speed = 1000;
	/**
	 * @desc the eight step sequence for a left rotation
	 */
	dataLeft[0] = 0b00001000; // decimal: 8
	dataLeft[1] = 0b00001100; // decimal: 12
	dataLeft[2] = 0b00000100; // ...
	dataLeft[3] = 0b00000110;
	dataLeft[4] = 0b00000010;
	dataLeft[5] = 0b00000011;
	dataLeft[6] = 0b00000001;
	dataLeft[7] = 0b00001001;
}

void stop() {
	for (int stepperPin = 0; stepperPin < NUM_STEPPER_PINS; stepperPin++) {
		digitalWrite(stepperPins[stepperPin], LOW);
	}
}

void turnRight(){
	/**
	 * @desc the stepper rotation leftward
	 */
	for (int i = 0; i < NUM_DATA; i+=1) {
		for (int stepperPin = 0; stepperPin < NUM_STEPPER_PINS; stepperPin+=1) {
			stepperPinState = bitRead(dataLeft[i], stepperPin);
			// Serial.print(stepperPinState);
			digitalWrite(stepperPins[stepperPin], stepperPinState);
			delayMicroseconds(100);
		}
	}
}

void turnLeft () {
	/**
	 * @desc the stepper rotation rightward
	 */
	for (int i = NUM_DATA - 1; i >= 0; i--) {
		for (int stepperPin = 0; stepperPin < NUM_STEPPER_PINS; stepperPin++) {
			stepperPinState = bitRead(dataLeft[i], stepperPin); // 1 = HIGH, 0 = LOW
			digitalWrite(stepperPins[stepperPin], stepperPinState);
			delayMicroseconds(speed);
		}
	}
}

void loop() {
	turnRight();
}
