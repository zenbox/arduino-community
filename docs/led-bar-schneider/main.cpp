#include <Arduino.h>

/**
 * @name
 * @desc  [use the tab key to step forward ...]
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/05
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

const byte STORAGE_CLOCK_PIN = 8 ;  //STCP
// const byte CLEAR_PIN =
const byte DATA_PIN = 11 ; // DS
const byte SERIAL_CLOCK_PIN = 12 ; //SHCP
long randNumber = 0;
long number = 0;

const int NUMBER_OF_SIGNS = 14 ;
byte dataArray[NUMBER_OF_SIGNS];
byte dataByte;


 void setup() {

Serial.begin(9600);
pinMode(STORAGE_CLOCK_PIN,OUTPUT);
pinMode(DATA_PIN,OUTPUT);
pinMode(SERIAL_CLOCK_PIN,OUTPUT);

//digitalWrite(SERIAL_CLOCK_PIN, HIGH);
//digitalWrite(DATA_PIN, LOW);
//digitalWrite(STORAGE_CLOCK_PIN, LOW);

dataArray[0] = B10000000; // one byte
dataArray[1] = B01000000; // one byte
dataArray[2] = B00100000; // one byte
dataArray[3] = B00010000; // one byte
dataArray[4] = B00001000; // one byte
dataArray[5] = B00000100; // one byte
dataArray[6] = B00000010; // one byte
dataArray[7] = B00000001; // one byte
dataArray[8] = B00000010; // one byte
dataArray[9] = B00000100; // one byte
dataArray[10] = B00001000; // one byte
dataArray[11] = B00010000; // one byte
dataArray[12] = B00100000; // one byte
dataArray[13] = B01000000; // one byte


 }

void shift(int DATA_PIN, int SERIAL_CLOCK_PIN, byte dataByte){
// @param byte dataByte a single byte to set the LED bar
int i =0;
int bitState;

digitalWrite(SERIAL_CLOCK_PIN, LOW);
digitalWrite(DATA_PIN, LOW);

for (i=7; i>=0; i-=1){
digitalWrite(SERIAL_CLOCK_PIN, LOW);

if(dataByte & (1<<i)){
bitState = HIGH;
}
else {
  bitState = LOW;
}

digitalWrite(DATA_PIN,bitState);
digitalWrite(SERIAL_CLOCK_PIN, HIGH);
digitalWrite(DATA_PIN, LOW);
}

digitalWrite(SERIAL_CLOCK_PIN, LOW);

}

void loop() {

for (int i=0; i<NUMBER_OF_SIGNS; i+=1){
digitalWrite(STORAGE_CLOCK_PIN,LOW);
shift(DATA_PIN, SERIAL_CLOCK_PIN, dataArray[i]);  //send byte
digitalWrite(STORAGE_CLOCK_PIN,HIGH);
delay(1000);
}

//number ++
// randNumber = random(0,255);
// byte(randNumber);
 }
