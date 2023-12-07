#include <U8g2lib.h>

#define STEP_PIN 12
#define DIR_PIN 11
#define ENA_PIN 10
#define ALM_PIN 13
#define BUTTON_PIN 2
#define LED_PIN 3
#define STEP_DELAY 8000
#define STEPS 1000
#define POT_PIN A3


U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

boolean motorState = LOW;
boolean ledState = LOW;
boolean buttonState = LOW;
unsigned int i = 0;
unsigned long steps = 20000;
unsigned long stepDelay = 500;
unsigned long stepDelayMin = 100;
unsigned long stepDecrease = 2;
unsigned potValue;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ALM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  potValue = analogRead(POT_PIN);

  myOled.begin();
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  Serial.begin(9600);

  digitalWrite(ENA_PIN, LOW); // ENABLE is active LOW
  digitalWrite(DIR_PIN, HIGH); // Set direction

}

void loop() {

  potValue = analogRead(POT_PIN);
  stepDelay = map(potValue, 0, 1023, 0, 1000);

  // rotate a step
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
  delayMicroseconds(stepDelay);

  // Increase speed
  // if (stepDelay > stepDelayMin) stepDelay -= stepDecrease;

  // Count steps
  i++;

  // Stop rotation
  if (i > steps) {
    motorState = LOW;
    digitalWrite(ENA_PIN, HIGH); // Disable stepper
    motorState = LOW;
    digitalWrite(LED_PIN, LOW);
  }

  // Print messages
  myOled.firstPage();
  do {

    // Write a text
    myOled.setFont(u8g2_font_6x13_te);

    myOled.setCursor(10, 16);
    myOled.print("delay:");
    myOled.setCursor(64, 16);
    myOled.print(stepDelay);

    myOled.setCursor(10, 36);
    myOled.print("steps:");
    myOled.setCursor(64, 36);
    myOled.print(i);

  } while ( myOled.nextPage() );

}
