#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup()
{
   Serial.begin(9600);

  motor1.setSpeed(150);
    motor2.setSpeed(150);
      motor3.setSpeed(150);
        motor4.setSpeed(150);
}

void loop()
{
     motor1.run(FORWARD);
     motor2.run(FORWARD);
     motor3.run(FORWARD);
     motor4.run(FORWARD);

//  delay(1000);
}







 void GO_FORWARD()
 {
     motor1.run(FORWARD);
     motor2.run(FORWARD);
     motor3.run(FORWARD);
     motor4.run(FORWARD);
   
 }
 
 void TURN_LEFT()
 {
     motor1.run(BACKWARD);
     motor2.run(FORWARD);
     motor3.run(FORWARD);
     motor4.run(BACKWARD);
 }
 
   void TURN_RIGHT()
   {
    motor1.run(FORWARD); 
    motor2.run(BACKWARD); 
    motor3.run(BACKWARD); 
    motor4.run(FORWARD);  
     
   }
   
  void GO_BACK()
  {
    motor1.run(BACKWARD); 
    motor2.run(BACKWARD); 
    motor3.run(BACKWARD); 
    motor4.run(BACKWARD); 
    
  }
  
  void RELEASE_ALL()
  {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE); 
  }
