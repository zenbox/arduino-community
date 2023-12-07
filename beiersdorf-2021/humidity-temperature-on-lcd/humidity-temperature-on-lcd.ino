/*
   Temperature/humidity in LCD display
   @version 1.0.0
   @author Michael
*/
// Prerequisite
#include <LiquidCrystal.h>
#include "DHT.h"

// 1. Declaration of variables
// DHT
// - - - - - - - - - -
#define DHTPIN 10     // const int DHTPIN = 10;
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// LCD
// - - - - - - - - - -
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// 2. Setup while board starts
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("initialising ...");
}


// 3. Code runs while board has current
void loop() {
  // DHT
  // - - - - - - - - - -
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  // isnan -> is not a number
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0, 1);
    lcd.print("Failed to read from DHT sensor!");
    return;
  }

  // lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Hum.:  ");
  lcd.print(h);
  lcd.print(" %");
  lcd.print("     ");

  lcd.setCursor(0, 1);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.print("      ");
}
