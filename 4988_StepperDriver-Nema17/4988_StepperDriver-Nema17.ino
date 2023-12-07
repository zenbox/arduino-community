/*
  Ansteuerung eines NEMA 17 Schrittmotors
  über einen 4988 Motor Treiber

   8 ──  EN    o         o VMOT ── Motor 12V (external)
  10 ──  MS1   o         o GND  ── Motor GND
  11 ──  MS2   o ┌────┐  o 2B   ── Motor Coil 2B
  12 ──  MS3   o │4988│  o 2A   ── Motor Coil 2A
     ┌── RST   o └────┘  o 1B   ── Motor Coil 1B
     └── SLEEP o         o 1A   ── Motor Coil 1A  
   5 ──  STEP  o         o VDD  ── Arduino 5V
   2 ──  DIR   o         o GND  ── Arduino GND

  2022, Michael Reichart
  copyleft CC BY-NC-SA
*/

// Declarations
#define ENABLE  8
#define MS1    10
#define MS2    11
#define MS3    12
#define STEP    5
#define DIR     2

int delayTimeMax = 1400;
int delayTimeMin = 650;
int delayTime;

void setup() {
  Serial.begin(115200);

  // 4988 Stepper board
  // Stepper board pin configuration
  // step, dir as output
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  // Enable the stepper
  digitalWrite(ENABLE, LOW);

  // Set the direction, clockwise?
  digitalWrite(DIR, HIGH);

  // Set the start speed
  delayTime = delayTimeMax;

  /* Microstepping configuration
     MS1 MS2 MS3 Microstep Resolution Excitation Mode
     L   L   L   Full Step                2 Phase
     H   L   L   Half Step              1-2 Phase
     L   H   L   Quarter Step          W1-2 Phase
     H   H   L   Eighth Step          2W1-2 Phase
     H   H   H   Sixteenth Step       4W1-2 Phase
  */
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);

  delayTimeMin = int(delayTimeMin / 16);
}

void loop() {
  digitalWrite(STEP, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(STEP, LOW);
  delayMicroseconds(delayTime);

  if (delayTime > delayTimeMin) {
    delayTime -= 1;
  }
}
