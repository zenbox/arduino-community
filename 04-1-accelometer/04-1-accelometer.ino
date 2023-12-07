#include <U8g2lib.h>
#include <Wire.h>
#include <math.h>

#define PINTASTER 12 // Pinnummer für den Taster

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Instanz für OLED Display

bool mod_run;   // Flag für den Betriebszustand
bool pressed;   // Status des Tasters zur Entprellung
uint8_t sl = 0; // Level für Kalibrierung

float x0, y0, z0;         // Nullpunkte
float xa, ya, za;         // Amplituden
int xlast = 0, ylast = 0; // Vorheriger Messwert

// Diese Funktion bereitet das Display zur Anzeige vor
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

// Messwerte anzeigen
void showMessung() {
  int x, xneu;
  int y, yneu;
  int z;
  float wx, wy, wz;
  char tmp[10];

  // Werte einlesen
  xneu = analogRead(A0) - x0;
  yneu = analogRead(A1) - y0;
  z    = analogRead(A2) - z0;

  // Mittelwertbildung um Rauschen zu reduzieren
  x = (xneu + xlast) / 2;
  y = (yneu + ylast) / 2;
  xlast = xneu;
  ylast = yneu;

  // Winkel berechnen
  wx = asin(x / xa) * 180 / M_PI;
  wy = asin(y / ya) * 180 / M_PI;
  wz = asin(z / 73.0) * 180 / M_PI;

  // Zur Kontrolle auf die Konsole ausgeben
//  Serial.print(x);  // Serial.print(",");
//  Serial.print(y);   Serial.print(",");
//  Serial.print(z);   Serial.print(",");
//  Serial.print(wx);  Serial.print(",");
//  Serial.print(wy);  Serial.print(",");
//  Serial.print(wz); 
//  Serial.println();

Serial.write(x);

  // Anzeige am Display
  u8g2.clearBuffer();
  u8g2_prepare();

  // Kreis für den Sollwert
  u8g2.drawCircle(32, 32, 5);

  // Punkt für den Istwert
  u8g2.drawDisc(32 - (x * 2), 32 + (y * 2), 2);

  // X-Winkel
  u8g2.drawStr(50, 10, "X = ");
  dtostrf(wx, 3, 1, tmp);
  u8g2.drawStr(80, 10, tmp);

  // Y-Winkel
  u8g2.drawStr(50, 30, "Y = ");
  dtostrf(wy, 3, 1, tmp);
  u8g2.drawStr(80, 30, tmp);
  u8g2.sendBuffer();
}

// Kalibrierungsanweisungen anzeigen
void showSetup(uint8_t level) {
  u8g2.clearBuffer();
  u8g2_prepare();
  switch (level) {
    case 0 :
      u8g2.drawStr(10, 30, "flach hinlegen");
      break;
    case 1 :
      u8g2.drawStr(10, 30, "90 Grad hochkippen");
      break;
    case 2 :
      u8g2.drawStr(10, 30, "90 Grad seitlich kippen");
      break;
  }
  u8g2.sendBuffer();
}

// Setup
void setup() {
  Serial.begin(9600);
  u8g2.begin();
  //Pin für Taster auf Input setzen
  pinMode(PINTASTER, INPUT_PULLUP);
  //Modus auf Kalibrierung
  mod_run = false;
}

void loop() {
  // Taster einlesen
  uint8_t taster = digitalRead(PINTASTER);
  if ((taster == 0) && (!pressed)) {
    // Wenn der Wert 0 ist und der Taster noch nicht gedrückt wurde
    // registrieren wir, dass der Taster jetzt gedrückt wurde
    pressed = true;
  }
  if ((taster == 1) && (pressed)) {
    // Wenn der Wert 1 ist und der Taster gedrückt war,
    // wurde er jetzt losgelassen
    pressed = false;

    if (mod_run) {
      // Wenn wir im Messmodus waren, schalten wir in den Kalibrierungs Modus
      // und setzen den Kalibrierungslevel auf 0
      mod_run = false;
      sl = 0;
    } else {
      // Wir sind im Kalibrierungsmodus und müssen
      // je nach Level die Kalibrierungswerte erfassen
      sl++;
      switch (sl) {
        // Das Gerät liegt flach X und Y sind 0 Z ist ´Maximum
        case 1:
          x0 = analogRead(A0);
          y0 = analogRead(A1);
          za = abs(analogRead(A2));
          break;
        // Das Gerät wurde nach oben gekippt Z ist jetzt 0 und X ist Maximum;
        case 2:
          z0 = analogRead(A2);
          xa = abs(analogRead(A0));
          break;
        // Das Gerät ist seitlich Y ist Maximum
        case 3:
          ya = abs(analogRead(A1));
          break;
      }

      // Wir haben alle nötigen Werte und können die Kalibrierungswerte setzen
      // anschließen wird der Mess Modus aktiviert
      if (sl > 2) {
        // Die Amplituden werden relativ zum Nullpunkt ermittelt
        // die Multiplikation mit 1.0 stellt sicher, dass wir
        // eine Fließkommazahl haben
        xa = xa - x0 * 1.0;
        ya = ya - y0 * 1.0;
        za = za - z0 * 1.0;
        mod_run = true;
      }
    }
  }
  // Je nach Modus wird die Anzeige entsprechend umgeschaltet
  if (mod_run) {
    showMessung();
  } else {
    showSetup(sl);
  }

  delay(200);
}
