#include <U8g2lib.h>
#include <Servo.h>
#include <AccelStepper.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Initialize Adafruit ST7789 TFT library
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
Servo myServo;
AccelStepper stepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

// Constants !!! ///
const byte BUTTON_PIN = 7;
const byte SERVO_PIN = 6;
const byte POT_PIN = A1;
const bool DEBUG = true;

// variable
bool solidState = true;
bool uiButtonState = true;
bool buttonState = false;
bool flag = false;

int sufficientTime = 200;

unsigned long currentTs;
unsigned long previousTs;
unsigned long pastTime = 0;
unsigned int potValue;
unsigned int servoValue;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  // - - - - -
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  // - - - - -
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  // - - - - -
  Serial.println(F("Initialized"));
  // - - - - -
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(400);
  stepper.setAcceleration(20);
  stepper.moveTo(500 * 64);
  // - - - - -
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font

  u8g2.setCursor(0, 10);
  u8g2.print("Temp.: ");  // write something to the internal memory
  u8g2.setCursor(50, 10);
  u8g2.print("Hallo Welt");  // write something to the internal memory

  u8g2.sendBuffer();  // transfer internal memory to the display
  delay(1000);
}

void loop() {
  // - - - - - -
  // Calc first
  // - - - - - -
  bool act = false;
  unsigned long myTime = millis() / 1000;
  unsigned long currenttime = millis();

  // if (currenttime - previoustime_1 >= zeit_1) act = true;

  // - - - - - -
  // Servo control
  // - - - - - -
  potValue = analogRead(POT_PIN);
  servoValue = map(potValue, 0, 1023, 180, 760);
  myServo.write(servoValue);
  // - - - - - -

  // - - - -
  // Stepper control
  // - - - -
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run();
  // - - - -

  // - - - - - -
  // OLED control
  // - - - - - -
  u8g2.clearBuffer();
  // - - - - -
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(20,40);
  u8g2.print("Hallo Welt");
      u8g2.setFont(u8g2_font_open_iconic_weather_2x_t);
      u8g2.drawGlyph(5, 20, 69);	// Sonne
      u8g2.drawGlyph(30, 20, 65);	// Sonne und Wolken
      u8g2.drawGlyph(55, 20, 64);	// Wolken
      u8g2.drawGlyph(5, 45, 67);	// Regen
      u8g2.drawGlyph(30, 45, 68);	// Stern
      u8g2.drawGlyph(55, 45, 66);	// Mond
  // - - - - -
  u8g2.sendBuffer();

  // - - - - - -

  buttonState = digitalRead(BUTTON_PIN);

  currentTs = millis();
  pastTime = currentTs - previousTs;

  if (pastTime >= sufficientTime) {


    if (buttonState == LOW) {
      delay(20);  // Entprellen

      previousTs = currentTs;
      uiButtonState = !uiButtonState;
      if (uiButtonState) {

        if (DEBUG) Serial.println("on");
      } else {

        if (DEBUG) Serial.println("reverse");
      }

      delay(200);  // Zeit, den Taster loszulassen
    }
  }
}
