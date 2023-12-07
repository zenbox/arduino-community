
const byte BTN_PIN = 2;
bool btnState;
int count = 0;
int maxCount = 3;

long timestamp = 0;
long oldTimestamp, currentTimestamp, diffTimestamp;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  pinMode(BTN_PIN, INPUT);
  btnState = digitalRead(BTN_PIN);
  Serial.println(btnState);

  timestamp = millis();
  Serial.println(timestamp);
}

void loop() {

  btnState = digitalRead(BTN_PIN);

  if (btnState == 1) {

    // Entprellen
    delay(20);

    count = count + 1;

    currentTimestamp = millis();
    diffTimestamp = currentTimestamp - oldTimestamp;
    oldTimestamp = currentTimestamp;
    Serial.print(diffTimestamp);
    Serial.println("ms");

    if (count > maxCount) count = 0;

    Serial.println(count);

    // Menschenzeit
    delay(1000);
  } else {
    // mach was, wenn der Taster nicht gedrückt ist
    switch (count) {
      case 0:
        Serial.print(timestamp);
        Serial.print(": Rot! (");
        Serial.print(diffTimestamp);
        Serial.println("ms)");
        break;
      case 1:
        Serial.print(timestamp);
        Serial.print(": Rot-Gelb (");
        Serial.print(diffTimestamp);
        Serial.println("ms)");
        break;
      case 2:
        Serial.print(timestamp);
        Serial.print(": Grün (");
        Serial.print(diffTimestamp);
        Serial.println("ms)");
        break;
      case 3:
        Serial.print(timestamp);
        Serial.print(": Gelb! (");
        Serial.print(diffTimestamp);
        Serial.println("ms)");
        break;
    }
    delay(500);
  }

}
