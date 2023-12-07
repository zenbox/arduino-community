#define A 2
#define B 3
#define C 4
#define D 5

#define NUMBER_OF_STEPS_PER_REV 512

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
}

void write(int a, int b, int c, int d) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
}

void onestep() {
  byte t =5;
  write(1, 0, 0, 0);
  delay(t);
  write(1, 1, 0, 0);
  delay(t);
  write(0, 1, 0, 0);
  delay(t);
  write(0, 1, 1, 0);
  delay(t);
  write(0, 0, 1, 0);
  delay(t);
  write(0, 0, 1, 1);
  delay(t);
  write(0, 0, 0, 1);
  delay(t);
  write(1, 0, 0, 1);
  delay(t);
}

void loop() {
  int i;
  i = 0;
  while (i < NUMBER_OF_STEPS_PER_REV) {
    onestep();
    i++;
  }
}
