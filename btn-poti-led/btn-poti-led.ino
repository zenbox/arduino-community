const byte LED_PIN = 3;
const byte BUTTON_PIN = 5;
const byte POTI_PIN = A1;

bool buttonState;
bool ledState;

bool flag = false;

unsigned int potiValue;
unsigned int ledValue;

// Zeit zählen
// ts = millis()
unsigned long currentTs = 0;
unsigned long previousTs = 0;
unsigned long pastTime = 0;
unsigned long sufficientTime = 100;

void blink(unsigned int count) {

  for (
    byte i = 0;
    i < count;
    i = i + 1) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("- - -");
  pinMode(BUTTON_PIN, INPUT);
  pinMode(POTI_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  potiValue = analogRead(POTI_PIN);

  blink(3);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  currentTs = millis();
  pastTime = currentTs - previousTs;

  if (pastTime >= sufficientTime) {
    // - - -
    if (flag == false) {
      flag = true;  // == bereit
      Serial.println("bereit");
    }

    if (buttonState == HIGH) {
      // Entprellen
      delay(20);

      previousTs = currentTs;
      ledState = !ledState;

      flag = false;  // == warten
      Serial.println("warte");

      // digitalWrite(LED_PIN, ledState);
      // Aktionspause für den Benutzer:
      // Zeit, den Taster loszulassen
      delay(200);
    }
    // - - -
    potiValue = analogRead(POTI_PIN);            // 0 - 1023
    // Serial.println(0);
    Serial.println(potiValue);
    // Serial.println(1023);
    // delay(100);
    ledValue = map(potiValue, 0, 1023, 0, 255);  // 0-255
    
    if(ledState){
      analogWrite(LED_PIN, ledValue);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    // - - -
  }
}
