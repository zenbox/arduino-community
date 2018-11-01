#include <Servo.h>

Servo servo1;

void setup()
{
  servo1.attach(2);
    servo1.write(125);
  delay(5000);
  servo1.write(90);
  delay(200);
    servo1.write(125);
  delay(710);

}

void loop()
{
  servo1.write(90);  //1
  delay(200);
    servo1.write(125);
  delay(600);

}
