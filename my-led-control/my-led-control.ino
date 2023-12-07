/*
    LED Kontrolle mit Taster und Potentiometer

    Schaltkreis:
    Led: Pin 6

    (c) 2023 Michael
    Version 1.0.0
*/


// Einrichten von GLOBALEN Variablen
// globaler Gültigkeitsbereich (Scope)!
// Ein 'flag', um den Fehler-Modus (debug) ein- oder auszuschalten
const bool DEBUG = true;


// Alternativ: #define LED_PIN 6
const byte LED_PIN = 6; // register length 1 byte
byte ledValue;

const byte POT_PIN = A1;
unsigned int potValue; // Poties liefern Werte zwischen 0 und 1023

const byte BUTTON_PIN = 2;
bool buttonState; // Taster liefern 1 | true | HIGH oder 0 | false | LOW

void setup() {
  if (DEBUG) {
    Serial.begin(9600); // Baud
  }

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Initiales Lesen von Potentiometer und Taster
  potValue = analogRead(POT_PIN);
  buttonState = digitalRead(BUTTON_PIN);

  // Initiales Rechnen der LED Helligkeit
  ledValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(LED_PIN, ledValue);
}

void loop() {
  // Auslesen des aktuellen Taster-Zustands
  buttonState = digitalRead(BUTTON_PIN);

  // Steuern der LED je nach Taster-Zustand
  if (buttonState == HIGH) {
    ledValue = 255;
  } else {
    // Helligkeit steuern
    potValue = analogRead(POT_PIN);
    ledValue = map(potValue, 0, 1023, 0, 255);
  }

  // Fehlerausgabe, wenn DEBUG == true
  if (DEBUG) {
    Serial.print("btn state: ");
    Serial.print(buttonState);
    Serial.println();
    Serial.print("pot value: ");
    Serial.print(potValue);
    Serial.println();
    delay(100);
  }

  analogWrite(LED_PIN, ledValue);
}
