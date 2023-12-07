#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Full buffer constructor
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// - - - - - - - - - -
// LDR sensor
const byte PIN_LDR = A0;
unsigned int valueLdr;
const int length = 128;
int list[length] = { 0 };
int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

void setup(void) {
  u8g2.begin();
}

void loop(void) {

  for (unsigned i = 1; i < 128; i++) {
    list[i - 1] = list[i];
  }
  list[127] = analogRead(PIN_LDR);

  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  u8g2.drawStr(0, 32, "Hello World!");  // write something to the internal memory

  for (int i = 0; i < (length - 1); i++) {
    y1 = map(list[i], 0, 1023, 0, 63);
    y2 = map(list[i + 1], 0, 1023, 0, 63);
    u8g2.drawLine(i, 64-y1, i + 1, 64-y2);
  }

  u8g2.sendBuffer();  // transfer internal memory to the display
  // delay(1000);
}