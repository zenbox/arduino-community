#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN  7

DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("hello, world!");

  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

//  if (isnan(h) || isnan(t) || isnan(f)) {
//    lcd.setCursor(0, 0);
//    lcd.print("Failed to read");
//    lcd.setCursor(0, 1);
//    lcd.print("from DHT sensor!");
//    return;
//  }

  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %\t");

  lcd.setCursor(0, 1);
  lcd.print("Tmp: ");
  lcd.print(t);
  lcd.print(" *C ");

}
