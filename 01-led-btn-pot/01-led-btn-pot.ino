#include <Arduino.h>

// Konstante Werte über den Interpreter in den Speicher schreiben
#define DEBUG false  // Debugging (Serieller Ausgabe) ist an/aus
#define LED_PIN 3
#define BTN_PIN 5
#define POT_PIN A1  // pin 15 (byte)

// Globale Variablen-Deklaration
bool buttonState;
bool ledState;  // 0 || 1, false || true, LOW || HIGH
bool uiState = false;

unsigned int potValue;  // A0 bis A5 liefern Spannungen (0V bis 5V) -> Digitalisierung mit 10bit:
byte ledValue;          // PWM von 0 bis 255

unsigned long currentTimeStamp = 0;  // in milliseconds 4 294 967 293 -> 49.71 Tage
unsigned long previousTimeStamp = 0;
unsigned long pastTime = 0;
unsigned int buttonInterval = 1000;  // Wartezeit zwischen zwei Taster-Drücken in Millisekunden

// - - - - - - - - - -
// - - - - - - - - - -
// - - - - - - - - - -

// Anschalten des Boards
void setup() {
  Serial.begin(2400);
  if (DEBUG) Serial.println("Setup");  // if (DEBUG == true) { ... }

  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  // Analoge Pins können nur einlesen
  // pinMode(A1, INPUT) kann man sich hier sparen
  // Im Setup sollte/muss der aktuelle Zustand
  // der Komponenten eingelesen werden!
  potValue = analogRead(POT_PIN);
}

// Betriebsprogramm
void loop() {

  // millis() - Liefert die Anzahl der Millisekunden seit den Start des Prozessors
  currentTimeStamp = millis();
  pastTime = currentTimeStamp - previousTimeStamp;  // Wieviel Zeit ist seit dem letzen Tasterdruck vergangen?

  // Taster
  buttonState = digitalRead(BTN_PIN);

  // Potentiometer
  potValue = analogRead(POT_PIN);  // 0 bis 1023

  int min = 0;
  int max = 1023;

  // Ausgabe im Seriellen Plotter
  Serial.print(min);
  Serial.print(" ");
  Serial.print(max);
  Serial.print(" ");
  Serial.println(potValue);

  if (pastTime >= buttonInterval) {
    // - - - - - -
    if (buttonState == HIGH) {
      delay(20);  // Entprellzeit

      previousTimeStamp = currentTimeStamp;  // Tasterdruck-Zeit merken

      // ! not
      ledState = !ledState;
      uiState = !uiState;

      if (DEBUG && uiState) Serial.println("active");
      if (DEBUG && !uiState) Serial.println("inactive");

      delay(100);  // Zeit, den Taster loszulassen
    }
    // - - - - -
  }

  // digitalWrite(LED_PIN, ledState);
  // LED kann gedimmt werden und leuchtet, wenn der ledState das erlaubt.
  if (ledState) { // Wenn ledState == true
    ledValue = map(potValue, 0, 1023, 0, 255);
    analogWrite(LED_PIN, ledValue);
  } else { // Sonst (wenn ledState != true)
    digitalWrite(LED_PIN, LOW);
  }
}
