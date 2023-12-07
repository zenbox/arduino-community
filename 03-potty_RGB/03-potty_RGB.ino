
int button = 8;
int buttonstate = 0;

//potty value 0 - 1023

int pottyR = A0;
int pottyG = A1;
int pottyB = A2;

int valR = 0;
int valG = 0;
int valB = 0;


//led value 0 - 255
 
int ledR = 9; 
int ledG = 10; 
int ledB = 11;

int LedValR = 0;
int LedValG = 0;
int LedValB = 0;

void setup() {

    Serial.begin(9600);
  
    pinMode(pottyR, INPUT);
    pinMode(pottyG, INPUT);
    pinMode(pottyB, INPUT);
    
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);

    pinMode(button, INPUT);
}

void loop() {
  valR = analogRead(pottyR);
  valG = analogRead(pottyG);
  valB = analogRead(pottyB);

  LedValR = map(LedValR, 0, 1023, 0, 255);
  LedValG = map(LedValG, 0, 1023, 0, 255);
  LedValB = map(LedValB, 0, 1023, 0, 255);

  buttonstate = digitalRead(button);

  analogWrite(ledR, LedValR);
  analogWrite(ledG, LedValG);
  analogWrite(ledB, LedValB);

  if (buttonstate == HIGH){
    Serial.println(LedValR);
    Serial.println(LedValG);
    Serial.println(LedValB);
    }
  }
  

  

