#include <DHT.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const bool DEBUG = false;
const byte LED_PIN = 3;
const byte BUTTON_PIN = 5;
const byte POTI_PIN = A1;

// #define DHTPIN 8
// #define DHTTYPE DHT11
const byte DHT_PIN = 8;

// DHT11 ist eine Konstante aus der Klasse DHT
DHT dht(DHT_PIN, DHT11);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);


bool buttonState;
bool ledState;

bool flag = false;

unsigned int potiValue;
unsigned int ledValue;

// Zeit zählen
// ts = millis()
unsigned long currentTs = 0;
unsigned long previousTs = 0;
unsigned long pastTime = 0;
unsigned long sufficientTime = 100;

void blink(unsigned int count) {

  for (
    byte i = 0;
    i < count;
    i = i + 1) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}

void display(float a = 3.14, float b = 9.81) {
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font

  u8g2.setCursor(0, 10);
  u8g2.print("Temp.: ");  // write something to the internal memory
  u8g2.setCursor(50, 10);
  u8g2.print(a);  // write something to the internal memory

  u8g2.setCursor(0, 30);
  u8g2.print("Hum.: ");  // write something to the internal memory
  u8g2.setCursor(50, 30);
  u8g2.print(b);  // write something to the internal memory

  u8g2.sendBuffer();  // transfer internal memory to the display
  delay(1000);
}

void showHumidityAndTemperature() {
  Serial.println("- - - H&T - - -");
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println(h);
  Serial.println(t);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  display(h, t);
  Serial.println("/- - - H&T - - -");
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();
  Serial.println("- - -");

  pinMode(BUTTON_PIN, INPUT);
  pinMode(POTI_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  display();

  potiValue = analogRead(POTI_PIN);

  blink(3);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  currentTs = millis();
  pastTime = currentTs - previousTs;

  if (pastTime >= sufficientTime) {
    // - - -
    if (flag == false) {
      flag = true;  // == bereit
      Serial.println("bereit");
    }

    if (buttonState == HIGH) {
      // Entprellen
      delay(20);

      previousTs = currentTs;
      ledState = !ledState;

      // + + + + + + + +
      delay(2000);
      float h = dht.readHumidity();
      float t = dht.readTemperature();

      Serial.println(h);
      Serial.println(t);

      // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }

      display(h, t);
      // + + + + + + + +

      flag = false;  // == warten
      Serial.println("warte");

      // digitalWrite(LED_PIN, ledState);
      // Aktionspause für den Benutzer:
      // Zeit, den Taster loszulassen
      delay(200);
    }
    // - - -
    potiValue = analogRead(POTI_PIN);  // 0 - 1023
    // Serial.println(0);
    if (DEBUG) Serial.println(potiValue);
    // Serial.println(1023);
    // delay(100);
    ledValue = map(potiValue, 0, 1023, 0, 255);  // 0-255

    if (ledState) {
      analogWrite(LED_PIN, ledValue);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    // - - -
  }
}
