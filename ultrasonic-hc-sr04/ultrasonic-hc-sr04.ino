

const byte TRIGGER_PIN = 9;
const byte ECHO_PIN = 10;

float duration, distance;



void setup() {
  Serial.begin(9600);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Messung beginnen
  // 10 Mikrosekunden lang Schall abgeben
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Messing abschließen
  duration = pulseIn(ECHO_PIN, HIGH);
  // In Entfernung umrechnen
  distance = (duration * .0343) / 2;

  float minDist = 4.27; // Soll: 3.0
  float maxDist = 29.52; // Soll: 29.7
  distance = map(distance, minDist, maxDist, 3.0, 29.7);

  // Ausgabe
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();

  // Warten vor der nächsten Messung
  delay(200);
}
