#include <Arduino.h>
/**
 * @name A eight led bar with 74HC595
 * @desc How to handle multiple led with n shift register IC
 *       and a binare data storage
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/05
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */
/**
 * @desc pin configuration
 *       Pins of 74HC595:
 *       ----------------
 *       SO    - Serial Data Output
 *       MR    - Master Reset (LOW active)
 *       SHCP  - Shift Register Clock Input
 *       STCP  - Storage Register Clock Input
 *       OE    - Output Enable Input (LOW active)
 *       DS    - Data Serial Input
 *
 *       D0-D7 - Parallel Data Output
 *       VCC   - Supply Voltage
 *       GND   - Ground
 *       ----------------
 *       http://www.nxp.com/documents/data_sheet/74HC_HCT595.pdf
 *       ----------------
 *
 * TIMETABLE
 * SHCP _|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_
 * DS   _______|¯¯¯|___________________________________|¯¯¯|_________________
 * STCP ___________|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|_|¯|
 * MR   ¯¯¯|___|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
 * OE   _____________________________________________|¯¯¯¯¯¯¯|_______________
 * Q0   ___________|¯¯¯|_____________________________________________________
 * Q1   _______________|¯¯¯|_________________________________________________
 * Q2   ___________________|¯¯¯|_____________________________________________
 * Q3   _______________________|¯¯¯|_________________________________________
 * Q4   ___________________________|¯¯¯|_____________________________________
 * Q5   _______________________________|¯¯¯|_________________________________
 * Q6   ___________________________________|¯¯¯|_____________________________
 * Q7   _______________________________________|¯¯¯|_________________________
 */
const int STCP = 7;   // STCP
const int MR   = 8;   //
const int DS  = 2;   // DS
const int SHCP = 4;   // SHCP

// data packages
const int NUM_DATA = 13;
byte dataArray[NUM_DATA];

// speed
int speed = 100; // ms

void setup () {
	// init a serial port
	Serial.begin(9600);
	Serial.print("Everything seems fine ...");

	// init the IC pins (75HC595)
	pinMode(STCP, OUTPUT);
	pinMode(MR, OUTPUT);
	pinMode(DS, OUTPUT);
	pinMode(SHCP, OUTPUT);

	digitalWrite(STCP, LOW);
	digitalWrite(MR,   LOW);
	digitalWrite(DS,  LOW);
	digitalWrite(SHCP, LOW);

	dataArray[0]  = 0b10000000;
	dataArray[1]  = 0b01000000;
	dataArray[2]  = 0b00100000;
	dataArray[3]  = 0b00010000;
	dataArray[4]  = 0b00000100;
	dataArray[5]  = 0b00000010;
	dataArray[6]  = 0b00000001;
	dataArray[7]  = 0b00000010;
	dataArray[8]  = 0b00000100;
	dataArray[9]  = 0b00001000;
	dataArray[10] = 0b00010000;
	dataArray[11] = 0b00100000;
	dataArray[12] = 0b01000000;
}

void shift (byte data) {
	/**
	 * @name shift
	 * @desc sends a single data byte
	 *       to the shift register
	 *
	 * @param byte dataByte a single data byte to set the led bar ...
	 * @return boolean
	 */
	boolean bitState;

	digitalWrite(MR, HIGH);
	digitalWrite(SHCP, LOW);
	digitalWrite(DS,  LOW);

	for ( int i=7; i>=0; i-- ) {
		digitalWrite(SHCP, LOW);

		if ( data & (1 << i)) {
			bitState = HIGH;
		} else {
			bitState = LOW;
		}

		digitalWrite(DS, bitState);
		digitalWrite(SHCP, HIGH);
		digitalWrite(DS, LOW);
	}

	digitalWrite(SHCP, LOW);
}

void loop () {
	digitalWrite(MR, HIGH); //

	for ( int i=0; i < NUM_DATA; i++) {
		digitalWrite(STCP, LOW);
		shift(dataArray[i]);
		digitalWrite(STCP, HIGH);
		delay(speed);
	}
}
