/**
   Steuerung der RGB Lichterkette über Arduino IR
   @version 1.0.0
   @author Michael
   @since 2018-11-01

   Codes:
   Repeat: 4294967295
   On/Off: 16761150
   CS:  16716270
   C3:  16724430
   C7:  16714230
   C16: 16722390

*/

#include <IRremote.h>

const int REPEATER = 4294967295;
const int ON_OFF = 16761150;
const int CS = 16716270;
const int C3 = 16724430;
const int C7 = 16714230;
const int C16 = 16722390;

const int RECV_PIN  = 11;
const int STATE_PIN = 13;
const int RED_PIN   = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN  = 6;

int count = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;
void setup()
{
  Serial.begin(9600);
  Serial.println("starting IR receive ...");
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
      case REPEATER:        // 1
        ping();
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        break;
      case ON_OFF:        // 2
        ping();
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        break;
      case CS:        // 3
        ping();
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        break;
      case C3:        // 3
        ping();
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        break;
      case C7:        // 3
        ping();
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        break;
      case C16:        // 3
        ping();
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        break;
      default:        // 3
        ping();
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
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
