const int IR_RECEIVER_PIN = A0;
const int LED_RED_PIN = 9;
const int LED_GREEN_PIN = 10;
const int LED_BLUE_PIN = 11;

int irReceiverValue = 0;
int numCount = 4;
int luminosityValue;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
}

void loop() {

  // read a hundred times
  for (int i = 0; i < numCount; i++) {
    irReceiverValue = analogRead(IR_RECEIVER_PIN);
    luminosityValue += irReceiverValue;
  }

  // calc the median
  luminosityValue = abs(luminosityValue / numCount);

  Serial.println(luminosityValue);
  //Serial.println(irReceiverValue);
  delay(25);
}
