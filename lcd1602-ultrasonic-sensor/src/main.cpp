#include <Arduino.h>
#include <LiquidCrystal.h>
/**
 * @name Ultrasonic HC-SR04 sensor and LCD1602 Display
 * @desc programming with complex components,
 *       using external libraries.
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/04
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

/**
 * @desc The display component pins are
 *       GND      Ground
 *       VCC      5V+
 *       V0       Constrad Adjustment
 *       RS       Register Selected Signal H/L
 *       R/W      Read/Write Signal H/L
 *       E        Enable Signal H/L
 *       LED+     LED Power Supply Anode
 *       LED-     LED Power Supply Ground
 *       DB 0-7   Databus H/L
 *       - - - - - - - - - -
 *       Use the LiquidCrystal class as an object instance
 *       The wiring scheme must be propagated via arguments
 *       in this order:
 *       RS, E, DS4, DS5, DS6, DS7
 */
LiquidCrystal lcd(12,11,5,4,3,2);

/**
 * @desc The ultrasonic HC-SR04 pins
 *       TRIGGER_PIN sends H/L from Arduino to ultrasonic
 *       ECHO_PIN    receives the ultrasonic measuring time
 */
const byte TRIGGER_PIN = 8;
const byte ECHO_PIN = 9;

// time and distance variables
float time = 0;
float cm = 0;

void setup() {
        Serial.begin(9600);

        // init the ultrasonic
        pinMode(ECHO_PIN, OUTPUT);
        pinMode(TRIGGER_PIN, INPUT);

        // init the display
        // number of columns, rows
        lcd.begin(16,2);
        lcd.clear();
}
void loop() {

        /**
         * @desc the ultrasonic measure timing diagram
         *       datasheet:
         *       http://www.electroschematics.com/wp-content/uploads/2013/07/HCSR04-datasheet-version-1.pdf
         *       trigger input to module
         *       __|¯¯¯¯¯|_____________________________|¯¯¯¯¯|__
         *
         *       ultrasonic module
         *       _________∏_∏_∏_∏_∏_∏_∏_∏_______________________
         *
         *       echo pin and pulseIn command
         *       _________________________|¯¯¯¯¯¯¯|_____________
         */
        // reset triger pin
        digitalWrite(TRIGGER_PIN, LOW);
        delayMicroseconds(2);

        // trigger input to module
        digitalWrite(TRIGGER_PIN, HIGH);
        delayMicroseconds(5);
        digitalWrite(TRIGGER_PIN, LOW);

      // now the ultrasonic module will perform
        // an 8 cycle sonic burst.

        // get the echo pulse output
        time = pulseIn(ECHO_PIN, HIGH);

        // calculating the distance from
        // a measuring time value in nano seconds
        // uS/58 = centimeters
        cm = time / 2 / 29;

        // output the distance
        lcd.setCursor(0, 1);
        lcd.print(cm);
        lcd.print(" cm ");

        delay(100);
}
