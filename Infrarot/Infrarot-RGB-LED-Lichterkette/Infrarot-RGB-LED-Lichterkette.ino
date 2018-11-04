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

const int RECV_PIN  = 6;
const int STATE_PIN = 13;
const int RED_PIN   = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;

int count = 0;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

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

  Serial.print("Sony: ");
  Serial.print(SONY);
  Serial.print(", NEC: ");
  Serial.print(NEC);
  Serial.print(", RC5: ");
  Serial.print(RC5);
  Serial.print(", RC6: ");
  Serial.print(RC6);
  Serial.print(", UNKNOWN: ");
  Serial.print(UNKNOWN);
  Serial.println();

}

void loop() {

//  for (int i = 0; i < 3; i++) {
//    irsend.sendNEC(1024, 12);
//    // Serial.print("sending ...");
//    delay(40);
//  }

  if (irrecv.decode(&results)) {

    //irsend.sendNEC(1024, 12);

    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.print(results.value, HEX);

    Serial.print(" (");
    Serial.print(results.value, DEC);
    Serial.print(")");

    Serial.print(", decode type: ");
    Serial.print(results.decode_type);
    Serial.print(", raw length: ");
    Serial.print(results.rawlen);
    Serial.print(", bits: ");
    Serial.print(results.bits);
    Serial.println();


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
