#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
void setup()
{
  Serial.begin(9600);
  pinMode (13, OUTPUT);
  digitalWrite(13, LOW);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    if (results.value == 1033561079) // 2
    {
      digitalWrite (13, HIGH);
    }
    if (results.value == 2534850111) // 1
    {
      digitalWrite (13, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
}
