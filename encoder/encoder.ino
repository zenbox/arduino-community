int clockP = A5;
int data = A4;
int count = 0;
int c = HIGH;
int cLast = HIGH;
int d = HIGH;

void setup() {
 pinMode (clockP,INPUT_PULLUP);
 pinMode (data,INPUT_PULLUP);
 Serial.begin (9600);
}

void loop() {
 c = digitalRead(clockP); // read pin A as clock
 d = digitalRead(data);  // read pin B as data

 if (c != cLast) {       // clock pin has changed value
   d = c^d;              // work out direction using an XOR
   if ( d ) {
     count++;
     Serial.print ("Right: ");
     Serial.println(count);
     delay(20);
   }else{
     count--;
     Serial.print ("Left: ");
     Serial.println(count);
     delay(20);
   }
   cLast = c;
 }
}
