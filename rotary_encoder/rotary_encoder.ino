
volatile int counter = 0;
volatile boolean a;
volatile boolean b;
volatile boolean oldA;

int v = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.begin(9600);
}

void loop() {

  a = digitalRead(2);

  if (digitalRead(2) == HIGH) Serial.println("2");
  if (digitalRead(3)) Serial.println("3");

  delay(5);
  //    oldA = a;
  //    a = HIGH;
  //
  //    if (encB.pressed() && a == oldA) {
  //      counter--;
  //      Serial.println("--");
  //    }
  //    else {
  //      counter++;
  //      Serial.println("++");
  //    }

  // Serial.println(counter, DEC);
  //  }

}
