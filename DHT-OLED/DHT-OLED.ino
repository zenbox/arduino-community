#include <Arduino.h>
#include <U8g2lib.h>
#include "DHT.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DHTPIN 7
#define DHTTYPE DHT11

U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);
DHT dht(DHTPIN, DHTTYPE);
uint8_t m = 24;
byte led = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  pinMode(13, OUTPUT);

  dht.begin();
  myOled.begin();

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  led = !led;
  digitalWrite(13, led);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(led);
  Serial.print("     ");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();

  char h_str[3];
  strcpy(h_str, u8x8_u8toa(h, 2));    /* convert m to a string with two digits */
  char t_str[3];
  strcpy(t_str, u8x8_u8toa(t, 2));    /* convert m to a string with two digits */

  myOled.firstPage();
  do {
    myOled.setFont(u8g2_font_logisoso24_tr);
    myOled.drawStr(0, 63, h_str);
    myOled.drawStr(35, 63, "%");
    myOled.drawStr(63, 63, t_str);
    myOled.drawStr(100, 63, "°C");
  } while ( myOled.nextPage() );

}
