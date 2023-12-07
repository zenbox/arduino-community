

#include <U8g2lib.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
const boolean DEBUG = true;
//
//const byte pirPin = 7;
//const byte relaisPin = 6;
//
//boolean pirState;
//boolean relaisState = LOW;

const byte photodiodePin = A0;
unsigned int photodiodeValue;
unsigned int calibratedValue;
int photodiodeValueList[128];
int listCounter = 0;


long calibratePhotodiode(byte analogPin) {
  unsigned int calibrationDuration   = 5000;
  unsigned long calibrationStarttime = millis();
  unsigned int calibrationAverageValue = 0;
  unsigned long photodiodeSum = 0;
  unsigned long counter = 0;

  do {
    photodiodeSum += analogRead(analogPin);
    counter++;
  } while ( millis() - calibrationStarttime <= calibrationDuration );

  calibrationAverageValue = photodiodeSum / counter;
  return calibrationAverageValue;
}

void setup() {
  Serial.begin(9600);

  oled.begin();
  Wire.begin();

  // - - - - - - - - - -
  // Configuration
  // - - - - - - - - - -
  //  pinMode(pirPin, INPUT);
  //  pinMode(relaisPin, OUTPUT);

  // - - - - - - - - - -
  // Initialisation
  // - - - - - - - - - -
  // pirState = digitalRead(pirPin);
  photodiodeValue = analogRead(photodiodePin);

  // - - - - - - - - - -
  // Calibration
  // - - - - - - - - - -
  calibratedValue = calibratePhotodiode(photodiodePin);

  /*
    //Put the HMC5883 IC into the correct operating mode
    Wire.beginTransmission(address); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();
  */
}

void loop() {

  /*
    // - - - - - - - - - -
    // PIR Motion Sensor
    // - - - - - - - - - -
    //  if (pirState) {
    //    relaisState = HIGH;
    //    digitalWrite(relaisPin, relaisState);
    //    delay(2500);
    //  } else {
    //    relaisState = LOW;
    //    digitalWrite(relaisPin, relaisState);
    //    delay(2500);
    //  }
  */
  /*
    // - - - - - - - - -
    // Compass Module
    // - - - - - - - - -
    //  int x, y, z; //triple axis data
    //  int xmin, xmax, ymin, ymax, zmin, zmax;
    //  xmin = 0; xmax = 0; ymax = 0; ymin = 0; zmin = 0; zmax = 0;
    //  //Tell the HMC5883 where to begin reading data
    //  Wire.beginTransmission(address);
    //  Wire.write(0x03); //select register 3, X MSB register
    //  Wire.endTransmission();
    //
    //
    //  //Read data from each axis, 2 registers per axis
    //  Wire.requestFrom(address, 6);
    //  if (6 <= Wire.available()) {
    //    x = Wire.read() << 8; //X msb
    //    x |= Wire.read(); //X lsb
    //    z = Wire.read() << 8; //Z msb
    //    z |= Wire.read(); //Z lsb
    //    y = Wire.read() << 8; //Y msb
    //    y |= Wire.read(); //Y lsb
    //  }

     //Print out values of each axis
    //  Serial.print("x: ");
    //  Serial.print(x);
    //  Serial.print("  y: ");
    //  Serial.print(y);
    //  Serial.print("  z: ");
    //  Serial.println(z);
    // - - - - - - - - - -
  */

  // - - - - - - - - - -
  // Photodiode value reading
  // - - - - - - - - - -
  photodiodeValue = analogRead(photodiodePin);
  photodiodeValueList[listCounter] = 48 + (photodiodeValue - calibratedValue);
  listCounter++;
  if (listCounter > 127) listCounter = 0;

  // - - - - - - - - - -
  // Oled Display
  // -> Data output
  // - - - - - - - - - -
  oled.firstPage();
  do {
    oled.setFont(u8g2_font_t0_14_me);

    oled.setCursor(0, 14);
    oled.print("Calib:");
    oled.setCursor(50, 14);
    oled.print(calibratedValue);

    oled.setCursor(0, 28);
    oled.print("Photo:");
    oled.setCursor(50, 28);
    oled.print(photodiodeValue);

    for (int i = 0; i <= 127; i++) {
      oled.drawPixel(i, photodiodeValueList[i]);
    }

  } while ( oled.nextPage() );
  // - - - - - - - - - -

  delay(10);

}
