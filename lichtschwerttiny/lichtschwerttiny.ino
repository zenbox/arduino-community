/**
 * Lichtschwert by Linus
 * @version 1.0.0
 * @since 2018-11-01
 * @author Linus
 *
 * AT Tiny:
 * Reset -| U |- 5V
 * A3, 3 -|   |- 2, A1
 * A2, 4 -|   |- 1 (PWM)
 * GND   -|   |- 0 (PWM)
 */

int ledR = 2;
int ledG = 3;
int ledB = 4;
int button = 5;
int buttonstate = 0;
int state = 1;
int power = 0;
int powerbutton = 6;
int powerbuttonstate = 0;
int active = 0;
int zeit = 100;
int on = 0;

void setup() {
        Serial.begin(9600);
        pinMode(ledR, OUTPUT);
        pinMode(ledG, OUTPUT);
        pinMode(ledB, OUTPUT);
        pinMode(button, INPUT);
        pinMode(powerbutton, INPUT);
}

void loop() {
        buttonstate = digitalRead(button);
        delay(20);
        powerbuttonstate = digitalRead(powerbutton);
        delay(20);
        if (buttonstate == HIGH)
                state = state + 1;
        delay(zeit);
        if (state > 3) {
                state = 1;
        }
        if (powerbuttonstate == HIGH ) {
                if (on == 0) {
                        power = 1;
                        on = 1;
                        delay(80);
                }
                else if (on == 1) {
                        power = 0;
                        on = 0;
                        delay(80);
                }
        }
        if (power == 0) {
                analogWrite(ledR, LOW);
                analogWrite(ledG, LOW);
                analogWrite(ledB, LOW);
        }

        if (power == 1) {


                switch (state) {
                case 1:
                        digitalWrite(ledR, HIGH);
                        digitalWrite(ledG, LOW);
                        digitalWrite(ledB, LOW);
                        break;
                case 2:
                        digitalWrite(ledR, LOW);
                        digitalWrite(ledG, HIGH);
                        digitalWrite(ledB, LOW);
                        break;
                case 3:
                        digitalWrite(ledR, LOW);
                        digitalWrite(ledG, LOW);
                        digitalWrite(ledB, HIGH);
                        break;
                }
                delay(zeit);
        }
}
