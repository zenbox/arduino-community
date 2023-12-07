
#include <Stepper.h> // Hinzufügen der Programmbibliothek.

// Declaration

// Data sheet?
int SPU = 2048; // Schritte pro Umdrehung.

// Use a library
// class Stepper { ... int setSpeed(velocity){ ... } }
// Initalize the library via constructor
Stepper Motor(SPU, 1, 3, 2, 4); // Der Schrittmotor erhält die Bezeichnung "Motor" und es wird angegeben an welchen Pins der Motor angeschlossen ist.

void setup() //Hier beginnt das Setup.
{
  Motor.setSpeed(15); // Angabe der Geschwindigkeit in Umdrehungen pro Minute.
}

void loop() {
  Motor.step(2048); // Der Motor macht 2048 Schritte, das entspricht einer Umdrehung.
  delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
  Motor.step(-2048); // Der Motor macht durch das Minuszeichen 2048 Schritte in die andere Richtung.
  delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
}
