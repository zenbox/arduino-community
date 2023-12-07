/*
  Hallo Andreas,
  hier findest du das letzte Script. Es kombiniert Display,
  Interrupt und die Kalibrieren-Funktion.

  Aufbau:
  Taster    - Pin 2  (Interrupt 0) (10kOhm Widerstand)
  LED       - Pin 13 (samt eingebautem Vorwiderstand)
  Fotodiode - A0     (samt 10kOhm Widerstand)
  Poti      - A1     (= regelbarer Widerstand 0 - 10 kOhm)
  OLED      - SCL -> A5, SDA -> A4

  2022, Michael Reichart
  copyleft CC BY-NC-SA
*/

// - - - - - - - - - -
// Einbinden von installierten Bibliotheken
// - - - - - - - - - -
#include <Arduino.h>
// - - - - -

// - - - - - - - - - -
// Global declarations
// - - - - -
const unsigned int photoDiodePin = A0;

unsigned int     potPin = A1;
unsigned int     potValue;

unsigned int     counter = 0;

unsigned int     ledPin = 13;
unsigned int     btnPin = 5; // Interrupt pin!
boolean          ledState = LOW;
volatile boolean btnState = LOW; // Volatile: interrupt-able variable!

unsigned int     calibrationValue = 0;
// - - - - -


// - - - - - - - - - -
// Calibration as an own function
// return type - function name - arguments - code
// - - - - -
long calibratePhotoDiode (unsigned int myAnalogPin) {

  // Local variables for this function
  unsigned int  calibrationDuration = 5000;
  unsigned long calibrationStart = millis();
  unsigned int  calibrationAverageValue = 0;
  unsigned long photoDiodeSum = 0;
  unsigned long counter = 0;

  // Measurements for an certain amount of time
  do {
    photoDiodeSum  += analogRead(myAnalogPin);

    Serial.println(analogRead(myAnalogPin));
    counter++;
  } while ( millis() - calibrationStart <= calibrationDuration );

  calibrationAverageValue = photoDiodeSum / counter;

  // Return the average value
  return calibrationAverageValue;
}

// - - - - - - - - - -
// An interrupt function
// - - - - -
void changeBtnState() {
  btnState = !btnState;
}
// - - - - -



void setup() {
  // - - - - - - - - - -
  // Attach interrupts
  // pin2 => interrupt pin 0
  // pin3 => interrupt pin 1
  // - - - - - - - - - -
  attachInterrupt(0, changeBtnState, RISING);


  Serial.begin(115200);
  // - - - - -
  pinMode(ledPin, OUTPUT);

  potValue = analogRead(potPin);


  // - - - - - - - - - -
  // Call the calibration method
  //    -> measurements for 5 seconds
  // - - - - -
  Serial.println("Calibration starts ... (5 seconds)");
  calibrationValue = calibratePhotoDiode(A0);
  Serial.print("Calibration average: ");
  Serial.print(calibrationValue);
  Serial.println();
}

void loop() {
  potValue = analogRead(potPin);
  ledState = btnState;
  digitalWrite(ledPin, ledState);

  Serial.print(potValue);
  Serial.println();

  delay(500);
}
