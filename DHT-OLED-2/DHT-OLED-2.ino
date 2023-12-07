#include <Arduino.h>
#include <U8g2lib.h>
#include "DHT.h"
#include <Wire.h>

#define DHTTYPE DHT11   // DHT 11

// Initalize the SSED1306 OLED
U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const byte DHTPIN = 8;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();

  oled.begin();
  oled.enableUTF8Print();
  oled.setFont(u8g2_font_6x12_me);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial output
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
  // - - - - - - - - - - -
  float f = round(t*10)/10;
    Serial.print(t);
    Serial.print(" ");
    Serial.println(f);
    
  oled.firstPage();
  do {
    oled.setCursor(0,32);
    oled.print(f);
    oled.print("°C");
  } while ( oled.nextPage() );
  // - - - - - - - - - - -
}
