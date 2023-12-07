#include <U8g2lib.h>

#define STEP_PIN 12
#define DIR_PIN 11
#define ENA_PIN 10
#define ALM_PIN 13
#define BUTTON_PIN 2
#define LED_PIN 3
#define STEP_DELAY 8000
#define STEPS 1000


U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

boolean motorState = LOW;
boolean ledState = LOW;
boolean buttonState = LOW;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ALM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  myOled.begin();
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    motorState = !motorState;
    delay(500);
  }

  if (motorState == HIGH) {
    forward(STEPS);
    delay(1000);
    reverse(STEPS);
    delay(1000);
  }
// - - - - - - - - - -
unsigned long millisBeforeOled = millis();
// - - - - - - - - - -
  myOled.firstPage();
  do {

    // Write a text
    myOled.setFont(u8g2_font_logisoso16_tr);
    myOled.setCursor(10, 40);
    myOled.print("hello world");

  } while ( myOled.nextPage() );
// - - - - - - - - - -
unsigned long millisAfterOled = millis();
// - - - - - - - - - -
Serial.println(millisAfterOled-millisBeforeOled);
// - - - - - - - - - -
}
void forward(int steps) {
  digitalWrite(LED_PIN, HIGH);

  digitalWrite(ENA_PIN, LOW); // ENABLE is active LOW
  digitalWrite(DIR_PIN, HIGH); // Set direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delayMicroseconds(STEP_DELAY);
  }
  digitalWrite(ENA_PIN, HIGH); // Disable stepper
  motorState = LOW;
  digitalWrite(LED_PIN, LOW);
}

void reverse(int steps) {
  digitalWrite(LED_PIN, HIGH);

  digitalWrite(ENA_PIN, LOW); // ENABLE is active LOW
  digitalWrite(DIR_PIN, LOW); // Set direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delayMicroseconds(STEP_DELAY);
  }
  digitalWrite(ENA_PIN, HIGH); // Disable stepper
  digitalWrite(LED_PIN, LOW);
}
