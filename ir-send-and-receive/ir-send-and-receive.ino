#include <IRremote.h>

#define PIN_IR_SEND 5
#define PIN_IR_DETECT 6

#define PIN_RED_STATUS 9
#define PIN_GREEN_STATUS 10
#define PIN_BLUE_STATUS 11

boolean irSendStatus = false;
boolean irDetectStatus = false;

IRsend irsend;
IRrecv irrecv(PIN_IR_DETECT);
decode_results results;

void red (int d = 50) {
  digitalWrite(PIN_RED_STATUS, HIGH);
  digitalWrite(PIN_GREEN_STATUS, LOW);
  digitalWrite(PIN_BLUE_STATUS, LOW);
  delay(d);
  digitalWrite(PIN_RED_STATUS, LOW);
  digitalWrite(PIN_GREEN_STATUS, LOW);
  digitalWrite(PIN_BLUE_STATUS, LOW);
}
void green (int d = 50) {
  digitalWrite(PIN_RED_STATUS, LOW);
  digitalWrite(PIN_GREEN_STATUS, HIGH);
  digitalWrite(PIN_BLUE_STATUS, LOW);
  delay(d);
  digitalWrite(PIN_RED_STATUS, LOW);
  digitalWrite(PIN_GREEN_STATUS, LOW);
  digitalWrite(PIN_BLUE_STATUS, LOW);
}
void blue (int d = 500) {
  digitalWrite(PIN_RED_STATUS, LOW);
  digitalWrite(PIN_GREEN_STATUS, LOW);
  digitalWrite(PIN_BLUE_STATUS, HIGH);
  delay(d);
  digitalWrite(PIN_RED_STATUS, LOW);
  digitalWrite(PIN_GREEN_STATUS, LOW);
  digitalWrite(PIN_BLUE_STATUS, LOW);
}
// Use this function instead of delay() as delay() does not work in interrupt callbacks
void pause(int ms) { 
    // We need a loop as the largest value for delayMicroseconds that will produce an accurate delay is 16383
    for (int i = 0; i < ms; i++) {
        delayMicroseconds(1000);
    }
}
void IREmitterOff() {
    irsend.space(0);
    pause(60); // 60 ms is OK for my TSOP but should be tuned
}

void IREmitterOn() {
    irsend.mark(0);
    pause(10);
}

void switchOffOnIREmitter() {
    IREmitterOff();
    IREmitterOn();
}

void checkIRBeamBreak() { 
    int val = digitalRead(PIN_IR_DETECT);
    // LOW : no beam break
    // HIGH : beam break
    if (val == LOW)
        return;

    detachInterrupt(digitalPinToInterrupt(PIN_IR_DETECT));
    
    switchOffOnIREmitter();
    if (digitalRead(PIN_IR_DETECT) == HIGH) {
        Serial.println("IR BEAM BREAK !!!!"); 
    }
    
    attachInterrupt(digitalPinToInterrupt(PIN_IR_DETECT), checkIRBeamBreak, RISING);
}
// - - - - - - - - - -
void setup()
// - - - - - - - - - -
{
  Serial.begin(9600);

  pinMode(PIN_IR_DETECT, INPUT);
  pinMode(PIN_IR_SEND, OUTPUT);

  pinMode(PIN_RED_STATUS, OUTPUT);
  pinMode(PIN_GREEN_STATUS, OUTPUT);
  pinMode(PIN_BLUE_STATUS, OUTPUT);

  Serial.println("READY");

  red(500);
  green(500);
  blue(500);

  attachInterrupt(digitalPinToInterrupt(PIN_IR_DETECT), checkIRBeamBreak, RISING);

  // irrecv.enableIRIn();

  //  Serial.println("Enable IR out");
  irsend.enableIROut(38);
  irsend.mark(0);
}

// - - - - - - - - - -
void loop()
// - - - - - - - - - -
{
  irDetectStatus = !digitalRead(PIN_IR_DETECT);

  if (irDetectStatus == true) {
    green();
  }

  if (irrecv.decode(&results)) {
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

    irrecv.resume(); // Receive the next value
  }
}
