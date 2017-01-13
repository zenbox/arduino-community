#include <Arduino.h>
//      #include <Stepper.h>
/**
 * @name stepper with poti
 * @desc how to control a stepper with potenciometer
 *
 * @package ArduinoBasics
 * @author Michael
 * @since 2017/01/12
 * @version 1.0.0
 * @copyright (c) Michael
 * @license MIT License <http://opensource.org/license/MIT>
 */

//declare a pin for the board
const byte PIN = 13;

//declare potentiometer
const int POTENTIOMETER_PIN = A1;
unsigned int potentiometerValue;
int servoAngle=0;
int servoSpeed=0;

//declare stepper
//Stepper stepper;
const int NUMBER_OF_STEPPER_PINS = 4;
int stepperPins[NUMBER_OF_STEPPER_PINS] = {7,6,5,4};

// stepper data
const int NUMBER_OF_DATA_STEPS=8;
byte data[NUMBER_OF_DATA_STEPS];

/**
 * @desc own functions
 *       must be written before setup and loop
 */
void turnLeft()
{
        boolean pinState;
        // iterate the stepper data
        for (int i = 0; i< NUMBER_OF_DATA_STEPS; i++)
        {
                for (int pin=0; pin< NUMBER_OF_STEPPER_PINS; pin++)
                {
                        pinState=bitRead(data[i], pin);
                        digitalWrite(stepperPins[pin], pinState);
                        delayMicroseconds(250);
                        servoSpeed = map(potentiometerValue,0,510,0,1000);
                        delayMicroseconds(servoSpeed);
                }
        }
}

void turnRight()
{
        boolean pinState;
        // iterate the stepper data
        for (int i = NUMBER_OF_DATA_STEPS-1; i>=0; i--)
        {
                for (int pin=NUMBER_OF_STEPPER_PINS; pin>=0; pin--)
                {
                        pinState=bitRead(data[i], pin);
                        digitalWrite(stepperPins[pin], pinState);
                        delayMicroseconds(250);
                        servoSpeed = map(potentiometerValue,511,1023,1000,0);
                        delayMicroseconds(servoSpeed);
                }
        }
}

void setup(){
        //init a serial port
        Serial.begin(9600);
        Serial.print("Everything seems fine...");

        //init LED pin
        pinMode (PIN, OUTPUT);

        //init potentiometer#
        potentiometerValue=analogRead(POTENTIOMETER_PIN);

        //generic stepper initialisation of the stepper pins
        for (int i =0; i<NUMBER_OF_STEPPER_PINS; i++)
        {
                pinMode(stepperPins[i], OUTPUT);

        }

        //Stepper data
        data[0] =0b1000;
        data[1] =0b1100;
        data[2] =0b0100;
        data[3] =0b0110;
        data[4] =0b0010;
        data[5] =0b0011;
        data[6] =0b0001;
        data[7] =0b1001;
}

void loop(){
        potentiometerValue=analogRead(POTENTIOMETER_PIN);
        servoAngle = map(potentiometerValue,0,1023,0,180);

        if (servoAngle < 90) {
                turnLeft();

        }
        else if (servoAngle>=90) {
                turnRight();

        }


}
