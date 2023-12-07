// Including a library
#include <Servo.h>

// Instancing the library object
Servo myservo;

int rotate = 20;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(rotate);
  delay(200);

  myservo.write(-rotate);
  delay(200);

}
