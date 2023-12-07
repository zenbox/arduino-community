#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int num = 1;

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();

  // The oscillator frequency of the pwm driver board
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  Wire.setClock(400000);
}

void loop() {


  //
  //  // Drive each PWM in a 'wave'
    for (uint16_t i=0; i<4096; i += 8) {
  
      for (uint8_t pwmnum=0; pwmnum < 8; pwmnum++) {
        pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
      }
  
    }
}
