int x=0; // Benennung von x als Variable für den Sensorwert der x-Achse
int y=0; // Benennung von y als Variable für den Sensorwert der y-Achse
int z=0; // Benennung von z als Variable für den Sensorwert der z-Achse

void setup() 
{
Serial.begin (115200); // Start der seriellen Verbindung für den serial monitor.
}

void loop() 
{
x=analogRead(A0); // Auslesen des Sensorwertes der x-Achse
y=analogRead(A1); // Auslesen des Sensorwertes der y-Achse
z=analogRead(A2); // Auslesen des Sensorwertes der z-Achse

//Serial.print (x); // Ausgabe des Sensorwertes der x-Achse an den serial monitor
//Serial.print ("    "); // Ausgabe von vier Leerzeichen
//Serial.print (y); // Ausgabe des Sensorwertes der y-Achse an den serial monitor
//Serial.print ("    "); // Ausgabe von vier Leerzeichen
//Serial.println (z); // Ausgabe des Sensorwertes der z-Achse an den serial monitor und Zeilenumsprung durch den Befehl "Serial.println"

float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                      //ADXL335 power supply by Vs 3.3V
float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
                       //330 * 1024/3.3/1000  
                       
Serial.print(((float)x - 331.5)/65*9.8);    // print x value on serial monitor
Serial.print("\t");
Serial.print(((float)y - 329.5)/68.5*9.8);  // print y value on serial monitor
Serial.print("\t");
Serial.print(((float)z - 340)/68*9.8);      // print z value on serial monitor
Serial.print("\n");

delay(1000); // Wartezeit zwischen den einzelnen Ausgaben der Sensorwerte
}
