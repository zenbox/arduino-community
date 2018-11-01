 #include <Servo.h>;
 
 int servoFrontPin = 12;
 int servoLeftPin = 10;
 int servoRightPin = 11;
 int pos = 0;

 Servo servoFront;
 Servo servoLeft;
 Servo servoRight;

 int servoLeftMin = 0 ;
 int servoLeftMax = 30;
 
 int servoRightMin = 30;
 int servoRightMax = 0;
 
 int servoFrontMin = 0;
 int servoFrontMax = 30;

 /*int servoLeftDif = 1; 
 int servoRightDif = 1;
 int servoFrontDif = 1;*/

 int servoLeftPos = servoLeftMin;
 int servoRightPos = servoRightMin;
 int servoFrontPos = servoFrontPos;

void setup() {
  servoFront.attach(servoFrontPin);
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);

  servoLeft.write(servoLeftMin);
  servoRight.write(servoRightMin);
  servoFront.write(servoFrontMin);

}

void loop() {

   servoLeft.write(servoLeftMin);
   servoRight.write(servoRightMin);
   servoFront.write(servoFrontMin);
   delay(500);
 
   servoLeft.write(servoLeftMax);
   servoRight.write(servoRightMax);
   servoFront.write(servoFrontMax);
   delay(500);
  }                 
  


