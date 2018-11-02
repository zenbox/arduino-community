#include "MOVIShield.h"
MOVI recognizer(true);
int light = 0;

void setup()
{
  pinMode(light, OUTPUT);
  recognizer.init();
  recognizer.callSign("Jasmin");
  recognizer.addSentence("hallo");
  recognizer.addSentence("tschüss");
  recognizer.addSentence("Licht an");
  recognizer.addSentence("Licht aus");
  recognizer.train();
  recognizer.setSynthesizer(SYNTH_PICO,"-l=de-DE");
  recognizer.setVolume(50);
  recognizer.responses(false);
}

void loop()
{
  int res = recognizer.poll();
  if (res == 1) {
    recognizer.say("hallo");
  }
  if (res == 2) {
    recognizer.say("Auf wiedersehen");
  }  
  if (res == 3) {
    light = HIGH;
    recognizer.say("licht aktiviert");
  }
  if (res == 4) {
    light = LOW;
    recognizer.say("licht deativiert");
  }  
  if (res == -502) {
    recognizer.say("das habe ich nicht verstanden");
  }
}
