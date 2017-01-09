#include <Arduino.h>
/**
 * @name Potentiometer with a threshold value
 * @desc
 *
 * @package Arduino Basics
 * @author Michael <michael@zenbox.de>
 * @since 2017/01/04
 * @version v1.0.0
 * @copyright (c) 2017 Michael Reichart
 * @license MIT License <http://opensource.org/licenses/MIT>
 */

const byte POTENTIOMETER_PIN = A0;
const byte LED_PIN = 13;
const byte LED_DIMMER_PIN = 11;

int potentiometerValue = 0;
int treshold = 512;
float voltage = 0;
byte pwmValue = 0;

void setup(){
  /**
   * @name setup
   * @desc a must have function!
   */
  Serial.begin(9600);

  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  /**
   * @desc read the current sensor values
   *       and save them in their variables
   */
  potentiometerValue = analogRead(POTENTIOMETER_PIN);

}

void loop(){
  /**
   * @name loop
   * @desc a must have function!
   */

  // read the analog value
  potentiometerValue = analogRead(POTENTIOMETER_PIN);
  Serial.print(potentiometerValue);
  Serial.println();

  // Spannungwert ausrechnen
  voltage = (potentiometerValue / 1023.0) * 5;
  Serial.print(voltage);
  Serial.print(" V");
  Serial.println();

  // LED fade in/out
  pwmValue = map(potentiometerValue, 0,1023, 0,255);
  analogWrite(LED_DIMMER_PIN, pwmValue);

  // HIGH the led, when sensor value is over threshold
  if (potentiometerValue >= treshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(50);
}
