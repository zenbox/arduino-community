#include <IRremote.h>

const int RECV_PIN  = 11;
const int STATE_PIN = 13;
const int RED_PIN   = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN  = 6;

IRrecv irrecv(RECV_PIN);

decode_results results;
void setup()
{
  Serial.begin(9600);
  // State LED
  pinMode (STATE_PIN, OUTPUT);
  digitalWrite(STATE_PIN, LOW);

  // RGB LED
  pinMode (RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  pinMode (GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, LOW);
  pinMode (BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, LOW);

  // Infrarot Empfaengerdiode
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {

    Serial.println(results.value, DEC);

    switch (results.value) {
      case 2534850111:        // 1
        ping(); digitalWrite(RED_PIN, HIGH);
        break;
      case 1033561079:        // 2
        ping(); digitalWrite(RED_PIN, LOW);
        break;
      case 2351064443:        // 4
        ping(); digitalWrite(GREEN_PIN, HIGH);
        break;
      case 1217346747:        // 5
        ping(); digitalWrite(GREEN_PIN, LOW);
        break;
      case 851901943:        // 7
        ping(); digitalWrite(BLUE_PIN, HIGH);
        break;
      case 465573243:        // 8
        ping(); digitalWrite(BLUE_PIN, LOW);
        break;
    }
   irrecv.resume(); // Receive the next value
  }
}

void ping () {
  digitalWrite (STATE_PIN, HIGH);
  delay(100);
  digitalWrite (STATE_PIN, LOW);
}
