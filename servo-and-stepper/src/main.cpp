#include <Arduino.h>
#include <Servo.h>

/**
 * @name servo and stepper
 * @desc how to control motors ...
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

/**
 * @desc a servo needs one data pin
 *       It must be a digital pin, because
 *       the servo data is a time based H/L sequence,
 *       not an analog value. The servo instance will be
 *       configured in the setup().
 *       Most servos needs an angle between 0 and 180 degree.
 *       The servo library is an Arduino standard lib.
 */
const byte SERVO_PIN = 3;
Servo servo_1;
int servoAngle;

// potentiometer configuration
const byte POTENTIOMETER_PIN = A3;
int potentiometerValue = 0;

void setup() {
								// init a serial port
								Serial.begin(9600);
								Serial.print("Everything seems fine ...");

								// init the led pin
								pinMode(PIN, OUTPUT);
								digitalWrite(PIN, LOW);

								/**
								 * @desc init the servo with the dedicated pin.
								 *       Alternatively with pin, startAngle, endAngle
								 *       attach(p, sa, ea).
								 *       The write() method send an angle to turn to.
								 */
								servo_1.attach(9);
								servo_1.write(servoAngle);

								// init the potentiometer
								potentiometerValue = analogRead(POTENTIOMETER_PIN);
}

void loop() {
								/**
								 *  @desc stearing the servo means i.e. easily mapping
								 *        the potentiometer values to a servo angle
								 *        and just send them.
								 */
								potentiometerValue = analogRead(POTENTIOMETER_PIN);
								servoAngle = map(potentiometerValue, 0,1023, 0,180);
								servo_1.write(servoAngle);

								// blink
								digitalWrite(PIN, HIGH);
								delay(500);
								digitalWrite(PIN, LOW);
								delay(500);
}
