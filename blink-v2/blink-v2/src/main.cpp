#include <Arduino.h>

  const byte LED_PIN_1 = 13;


void setup() {
  pinMode(LED_PIN_1, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN_1, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_1, LOW);
  delay(1000);

}

