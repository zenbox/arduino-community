#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

/**
 * @name SD_Card
 * @desc  [use the tab key to step forward ...]
 *
 * @package Arduino Basics
 * @author Schnu
 * @since 2017/01/06
 * @version v1.0.0
 * @copyright (c) 2017 Christian Schneider
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

const int POTENTIOMETER_PIN = A2;    //define input pin for the potentiometer
int potentiometerValue = 0;        //start value for the potentiometer
int cs = 10;  // Set Chip Select to pin ten

int i = 0;

File dataFile;  // a File Object
// make a string for assembling the data to log:
String dataString = "";

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);

	Serial.print("Initializing SD card...");

	// see if the card is present and can be initialized:
	if (!SD.begin(cs)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	}
	Serial.println("card initialized.");
}

void loop() {

while(i<20){
	// read three sensors and append to the string:
	potentiometerValue = analogRead(POTENTIOMETER_PIN); // get potentiometer value
	dataString += String(potentiometerValue);
	dataString += (",  ");

// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
	dataFile = SD.open("myfirstFile.txt", FILE_WRITE);

// if the file is available, write to it:
//	if (dataFile) {
	dataFile.println(dataString);
	dataFile.close();
	// print to the serial port too:
	Serial.println(dataString);

  i++;
	/*}
	   // if the file isn't open, pop up an error:
	   else {
	        Serial.println("error opening myfirstFile.txt");
	   }*/
   }
}
