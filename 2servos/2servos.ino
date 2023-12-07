/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo_1;  // create servo object to control a servo
Servo myservo_2;

int potpin = A1;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo_1.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo_2.attach(9); 
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 180, 0);     // scale it for use with the servo (value between 0 and 180)
  myservo_1.write(val);                  // sets the servo position according to the scaled value
  myservo_2.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
