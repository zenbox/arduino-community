#include <Arduino.h>

// - - - - -
// Global scoped variables
// - - - - -
// integer - Ganzzahlen; ohne Nachkommaanteil
// 0, 12, 3408, ...
// integer sind 2 Byte lang, 0 - 65535

const boolean DEBUG = false;

const byte LED_PIN = 3; // 0 - 255, 1 byte (8 bit)
const byte POT_PIN = A1;
const byte BTN_PIN = 5;
const byte LS_PIN = A0;

boolean ledState;
boolean btnState;

unsigned int potValue;
unsigned int lsValue;

long lsAverageValue = 0;

void setup() {
  // Serielle Ausgabe am Rechner
  Serial.begin(9600); // Baud-Rate (Übertragungsgeschwindigkeit)

  // Vorbereiten der Pins für ihre Aufgaben
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  // überflüssig: pinMode(A1, INPUT)
  // überflüssig: pinMode(A0, INPUT)

  // Aktuelle Zustände der Bauteile
  ledState = LOW;
  digitalWrite(LED_PIN, ledState); // Zustand auf aus setzen
  btnState = digitalRead(BTN_PIN); // Zustand abfragen
  potValue = analogRead(POT_PIN);
  lsValue = analogRead(LS_PIN);

  // Serielle Ausgabe eines Wertes
  if (DEBUG) Serial.println(potValue);

  // Aufruf der Lichtsensor Kalibration
  Serial.println("Kalibrierung ...");
  lsAverageValue = calibrateLightSensor(LS_PIN);
  Serial.println("...beendet: ");
  //  Serial.println(lsAverageValue);
}

// Funktion:
void loop() {
  // Wiederholtes Einlesen eines Wertes
  potValue = analogRead(POT_PIN);
  lsValue = analogRead(LS_PIN);
  btnState = digitalRead(BTN_PIN);

  // Testausgabe des LS Wertes
  //  Serial.print("LS_PIN: ");
  //  Serial.print(lsValue);
  //  Serial.println();

  Serial.println(lsAverageValue);

  if (btnState == HIGH) {
    if (DEBUG) Serial.println("Der Taster ist gedrückt.");
  } else if (btnState == -1) {
    if (DEBUG) Serial.println("Der Taster ist seltsam.");
  } else {
    if (DEBUG) Serial.println("Der Taster ist NICHT gedrückt");
  }

  // BEREICH ABFRAGEN
  //  if (potValue >= 0 && potValue <= 100) {
  //    Serial.println("Das Potentiometer ist zwischen 0 und 100.");
  //  } else if (potValue > 100 && potValue <= 400) {
  //    Serial.println("Das Potentiometer ist zwischen 101 und 400.");
  //  }

  if (btnState == HIGH) {

    int dimmedPotValue = map(potValue, 0, 1023, 0, 255); // 0 (LOW) - 255 (HIGH)
    analogWrite(LED_PIN, dimmedPotValue);

  } else {
    digitalWrite(LED_PIN, LOW);
  }

  if (DEBUG) Serial.print( btnState );
  if (DEBUG) Serial.print(" / ");
  if (DEBUG) Serial.print( potValue );
  if (DEBUG) Serial.println();

  // - - - - -
  //  float fDeg = 21.3;
  //  String sUnit = "Celsius";
  //
  //  char buffer[40];
  //  sprintf(buffer, "Temp: %d degree %s", fDeg, sUnit);
  //  Serial.println(buffer);
  // - - - - -

  delay(500);
}

/**
   @desc Kalibriert einen Lichtsensor mit eine Messreihe
         über 5 Sekunden und ermittelt den Durchschnittswert
*/
long calibrateLightSensor(byte lsPin) {
  Serial.println("calibrating ...");
  // lokale Variablen für diese Funktion
  unsigned int duration = 2000;
  unsigned int count = 1000;
  unsigned long averageValue = 0;
  unsigned long sum = 0;
  unsigned long counter = 0;
  unsigned int measureValue;
  unsigned long dif = 0;

  unsigned long startTime = millis();

  do {
    // Messungen durchführen
    measureValue = analogRead(lsPin);
    sum = sum + measureValue;
  } while ( (millis() - startTime) < duration );

  Serial.println("finished");
  delay(100);
//  Serial.println(millis());
  Serial.println(startTime);
  
  // Durchschnittswert berechnen
  averageValue = sum / counter;
  Serial.print("averageValue: ");
  Serial.print(averageValue);
  Serial.println();

  // Rückgabe eines Wertes an den Aufruf der Funktion (im setup)
  return averageValue;
}
