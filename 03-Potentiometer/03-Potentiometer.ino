
int potPin = A0;
int potValue;

void setup() {
  // Starten des seriellen Monitors
  // mit einer Datenrate von 9600 Baud
  Serial.begin(9600);
  Serial.println("Ready.");


   // Wichtig: Lesen des initialen Potentiometerwerts
   pinMode(potPin, INPUT);
   potValue = analogRead(potPin);
 }

void loop() {
   // Wiederholes Lesen des Potentiometerwertes
   potValue = analogRead(potPin);

   // Ausgabe des Wertes auf dem seriellen Monitor
   Serial.println(potValue);

   delay(100);

 }
