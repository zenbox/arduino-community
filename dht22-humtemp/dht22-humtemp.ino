// Einbinden von Bibliotheken
#include <DHT.h>
#include <U8g2lib.h>


#define DHTTYPE DHT22

const byte DHT_PIN = 8;

DHT dht(DHT_PIN, DHTTYPE);
U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 Test!"));

  dht.begin();

  oled.begin();
  oled.enableUTF8Print();

  oled.setFont(u8g2_font_6x12_me); // Auswahl der Schrift

}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //  Serial.print(F("Luftfeuchte: "));
  //  Serial.print(h);
  //  Serial.print(F("%  Temperatur: "));
  //  Serial.print(t);
  //  Serial.print(F("°C "));
  //  Serial.println();

  oled.firstPage();
  do {

    oled.setCursor(0, 32);
    oled.print("Temperatur: ");
    oled.print(t);
    oled.print("°C");

 
    oled.setCursor(0, 44);
    oled.print("Feuchte: ");
    oled.print(h);
    oled.print("% rel.");

  } while ( oled.nextPage() );
}
