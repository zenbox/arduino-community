#include <U8g2lib.h>

#define STEP_PIN 12
#define DIR_PIN 11
#define ENA_PIN 10

#define ALM_PIN 13
#define BUTTON_PIN 2
#define LED_PIN 3
#define POT_PIN A3

unsigned potValue;
unsigned stepDelay;
boolean ledState = LOW;
boolean buttonState = LOW;
int millisStart = millis();
boolean dirState = HIGH;
int automate = 0;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

void setup() {
  myOled.begin();

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ALM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(ENA_PIN, LOW);
  digitalWrite(DIR_PIN, dirState);

  potValue = analogRead(POT_PIN);
}

void loop() {

  buttonState = digitalRead(BUTTON_PIN);

  int t = millis() - millisStart;
  if (buttonState == HIGH && t > 200 ) {
    millisStart = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    automate++;
    if (automate > 2)automate = 0;

    switch (automate) {
      case 0:
      case 1:
        dirState = !dirState;
        digitalWrite(ENA_PIN, LOW); // Enable stepper
        digitalWrite(DIR_PIN, dirState);
        break;
      case 2:
        digitalWrite(ENA_PIN, HIGH); // Disable stepper
        break;


    }
    // Print messages
    myOled.firstPage();
    do {
      // Write a text
      myOled.setFont(u8g2_font_6x13_te);

      myOled.setCursor(10, 15);
      myOled.print("dir:");
      myOled.setCursor(64, 15);
      myOled.print(dirState);

      myOled.setCursor(10, 36);
      myOled.print("automate:");
      myOled.setCursor(64, 36);
      myOled.print(automate);

    } while ( myOled.nextPage() );
  }



  potValue = analogRead(POT_PIN);
  stepDelay = map(potValue, 0, 1023, 0, 8000);


  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
  delayMicroseconds(stepDelay);
}

void accelerate () {

}
