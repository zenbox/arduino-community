int sensor = 8; 
int Led1 = 10;
int Led2 = 11;
int object = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2,OUTPUT);
  pinMode(sensor, INPUT); 
}

void loop() {
  object = digitalRead(sensor);
  
  if(object == LOW) {
    Led2 = HIGH;
    Led1 = LOW; 
    }
  else{
    Led1 = HIGH; 
    Led2 = LOW; 
    }
}
