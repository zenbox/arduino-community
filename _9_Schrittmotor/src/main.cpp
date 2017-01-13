#include <Arduino.h>



/**
 * @name Schrittmotor
 * @desc wie man einen Schrittmotor konfiguriert (ohne Stepper libary)
 * Controle the servo angel.
 *
 * @packages Arduino Basics
 * @author Werner Fries
 * @since 2017/01/12
 * @copyright (c) 2017 Werner Fries
 * @license MIT License <http://opensource.org/licenses/MIT>
 */


/**
 * @desc the stepper confuguration
 */
const int NUMBER_OF_STEPPER_PINS = 4;
int stepperPins[NUMBER_OF_STEPPER_PINS] = {7,6,5,4};

// stepper data
const int NUMBER_OF_DATA_STEPS = 8;
byte data[NUMBER_OF_DATA_STEPS];



// eigene functionen einrichten
void turnRight() {
	boolean pinState;
	// iterate the stepper data
	for (int step=0; step<510; step++) {
		for (int i = 0; i < NUMBER_OF_DATA_STEPS; i++) {
			/* code */
			for (int pin = 0; pin < NUMBER_OF_STEPPER_PINS; pin++) {
				/* code */

// bei bitRead wird ein einzelnes Bit aus dem String ausgewertet
				pinState = bitRead(data[i], pin);
				digitalWrite (stepperPins [pin], pinState);
				delayMicroseconds(250);

			}
		}
	}
}



void turnLeft(){
	boolean pinState;

	for (int step=0; step<510; step++) {

		for (int i = NUMBER_OF_DATA_STEPS-1; i >=0; i--) {
			/* code */
			for (int pin = 0; pin < NUMBER_OF_STEPPER_PINS; pin++) {
				/* code */

// bei bitRead wird ein einzelnes Bit aus dem String ausgewertet
				pinState = bitRead(data[i], pin);
				digitalWrite (stepperPins [pin], pinState);
				delayMicroseconds(250);

			}
		}

	}

}


// the setup
void setup () {
	Serial.begin(9600);
	Serial.println("Alles ist gut");

// init the stepper PINS
	for (int i = 0; i < NUMBER_OF_STEPPER_PINS; i=i+1) {
		/* code */
		pinMode(stepperPins[i], OUTPUT);

	}

// @desc stepper data
// an eigt step sequence for a rotation
// with stepper 2BYJ-48
	data[0] = 0b00001000;
	data[1] = 0b00001100;
	data[2] = 0b00000100;
	data[3] = 0b00000110;
	data[4] = 0b00000010;
	data[5] = 0b00000011;
	data[6] = 0b00000001;
	data[7] = 0b00001001;


}
void loop () {
	turnRight();
	delay(1000);
	Serial.println("Jetzt gehts linksrum");
	turnLeft();
	delay(1000);
	Serial.println("Jetzt gehts rechtsrum");



}
