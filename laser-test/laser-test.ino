int laser = 9;
int moveSensor = 3;
int moveSensorState = 0; 
int val = 0;  

void setup() {
  pinMode(laser, OUTPUT);
  pinMode(moveSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(moveSensor);
  if(val == HIGH){
    digitalWrite(laser, HIGH);
    }
  else{
    digitalWrite(laser, LOW);
    if(moveSensorState == HIGH){
      Serial.println("Motion ended");
      moveSensorState = LOW;
      } 
    }
}
