#include <U8g2lib.h>


U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

int value = 0;

void setup() {
  myOled.begin();
}

void loop() {
  delay(2000);
  
  value = value + 1;
  if (value > 99) value = 0;

  char value_string[3];
  strcpy(value_string, u8x8_u8toa(value, 2));
  
  myOled.firstPage();
  do {
    myOled.setFont(u8g2_font_logisoso24_tr);
    myOled.drawStr(0, 63, value_string);
    myOled.drawStr(35, 63, "%");
  } while ( myOled.nextPage() );
}
