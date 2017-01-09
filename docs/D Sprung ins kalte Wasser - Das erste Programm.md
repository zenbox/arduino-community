# The Blink Example
	#include <Arduino.h>
	
	void setup() {
	  // Initialize digital pin LED_BUILTIN as an output.
	  // LED_BUILTIN and OUTPUT are fixed values.
	  pinMode(LED_BUILTIN, OUTPUT);
	}
	
	// the loop 
	// it runs over and over again forever
	void loop() {
	  // turn the LED on (HIGH is the voltage level)
	  digitalWrite(LED_BUILTIN, HIGH);
	
	  // wait for a second
	  delay(1000);
	  
	  // turn the LED off by making the voltage LOW
	  digitalWrite(LED_BUILTIN, LOW);
	  
	  // wait for a second
	  delay(1000);
	}

# Coding Conventions

Codes werden nach Konventionen und Standards geschrieben. Dies fördert das Verständnis und die Lesbarkeit der Quelltexte.

**Kommentare** erläutern Funktionen und Programmzeilen.

	// Einzeilenkommentar
	
	/* 
	   Mehrzeilenkommentar, der
	   in vielen Zeilen ...
	*/
	
	/**
	 * @name JavaDoc
	 * @desc ein Standardkommentar mit tagging
	 * @since 2016/12/25
	 * ...
	 */
	
**Includes** laden externe Bibliothek ein. Dies geschieht einmal fix am Anfang. 

	#include "Arduino.h"

# Begriffe der Programmierung

**Variablen**
Eine Variable stellt eine Platzhalter für beliebige Werte dar.

	int a = 42;

`a` ist der Name das Platzhalter. Eine neue Variable muss mit einem Wertetyp deklariert werden. `42` ist der Wert, der zugewiesen wird. Der Wertetyp legt fest, ob in einer Variablen ein Zahlenwert oder ein Literalwert gespeichert werden kann. In allen folgenden Programmzeilen kann über den Platzhalter `a` der Wert `42` abgerufen und verwendet werden. Bei Variablen kann der Wert jederzeit geändert werden.

	a = 108;

## Werte unterscheiden

**Wertetypen für Zahlen**

Im deutschen werden Dezimalzahlen an den Tausendern mit dem Punkt (2.147.483.648) notiert. Im englischen mit Kommas (2,147,483,648). Da Programmierung english ist, finden sich dort die Erläuterungen von großen Zahlen mit Kommas. In der eigentlichen Programmzeile wird ausser dem Punkt als Dezimaltrennzeichen nichts notiert (4008.14).

	byte          - Zahl zwischen 0 und 255 , kann dezimal oder auch binär
	                notiert werden. B10010 entspricht dezimal 18.
	int           - Ganzahl mit 2 Byte in einem Bereich von -32.768 to 32.767
	unsigned int  - Ganzahl ohne Vorzeichen mit 2 Byte zwischen 0 und 65.535
	short         - Ein 16-bit (2-Byte) Wert zwischen -32.768 to 32.767. 
	long          - Ganzzahl mit 4 Byte (32 Bit), -2.147.483.648 bis 2.147.483.647
	unsigned long - 4 Byte ohne Vorzeichen 0 bis  4.294.967.295.
	float         - Fließkommazahl mit 32 Bit (4 Byte), 
	                im Bereich von -3.4028235E+38 und 3.4028235E+38.
	                Fließkommazahlen haben eine begrenzte Genauigkeit 
	                von nur 6-7 Digits und sind nicht genau.
	double        - Auf Arduino Uno gibt es eigentlich keine doubles. Sie 
	                entsprechen den floats. Auf Arduino Due haben doubles 
	                8 Bytes (64 Bytes).
	char          - Ein Datentyp für ein Byte Speicher, der ein Zeichen speichert.
	                zum Beispiel 'a'. Zeichen werden i einfachen Anführungszeichen
	                notiert. Sie können auch durch deren Dezimalcode (im ASCII 
	                Standard ist A - 65) notiert werden.
	unsigned char - Entspricht den byte Typ.


# Blink with constant pins

	#include <Arduino.h>
	
	/**
	 * @name Blink with Constants
	 * @desc INTRODUCTION
	 *       first approach, use of constant values
	 *
	 * @package Arduino Basics
	 * @author Michael <michael@zenbox.de>
	 * @since 2016/12/25
	 * @version v1.0.1
	 * @copyright (c) 2017 Michael Reichart GmbH, Cologne
	 * @license MIT License [https://opensource.org/licenses/MIT]
	 */
	
	/**
	 * @desc declare a constant value
	 *       constant values will be set once in memory, they will never
	 *       change while processing the programm. They use les memory than
	 *       variable values. Constants uses UPPERCASE names by convention.
	 */
	const byte LED_PIN = 13;
	
	/* @name setup()
	 * @desc the setup function runs once when the board is started by
	 *       pressing you reset or empower the board. While setting up,
	 *       pins and serial can be configured.
	 */
	void setup() {
	  // setting up the serial port
	  Serial.begin(115200);
	
	  // initialize digital pin 13 as an output.
	  // OUTPUT is a Arduino constant value
	  pinMode(LED_PIN, OUTPUT);
	}
	
	/**
	 * @name loop
	 * @desc the loop function runs over and over again forever. It will
	 *       runs the prozess while, the board has power.
	 */
	void loop() {
	  // turn the LED on
	  digitalWrite (LED_PIN, HIGH );
	
	  // wait for a second
	  delay(1000);
	
	  // turn the LED off
	  digitalWrite(LED_PIN, LOW);
	
	  // wait for a second
	  delay(1000);
	}
	

# Traffic Lights 1

	#include <Arduino.h>
	
	/**
	 * @name Traffic Lights
	 * @desc INTRODUCTION
	 *       a red, yellow and green led blinking
	 *
	 * @package Arduino Basics
	 * @author Michael <michael@zenbox.de>
	 * @since 2016/12/25
	 * @version v1.0.1
	 * @copyright (c) 2017 Michael Reichart GmbH, Cologne
	 * @license MIT License [https://opensource.org/licenses/MIT]
	 */
	
	// declare constant values for the pins
	const byte RED = 3;
	const byte YELLOW = 6;
	const byte GREEN = 5;
	
	/* @name setup()
	 * @desc the setup function runs once when the board is started by
	 *       pressing you reset or empower the board. While setting up,
	 *       pins and serial can be configured.
	 */
	void setup() {
	  // setting up the serial port
	  Serial.begin(115200);
	
	  // initialize digital pins as an output. 
	  pinMode(RED, OUTPUT);
	  pinMode(YELLOW, OUTPUT);
	  pinMode(GREEN, OUTPUT);
	
	  // init the pin voltage as LOW
	  digitalWrite(RED, LOW);
	  digitalWrite(YELLOW, LOW);
	  digitalWrite(GREEN, LOW);
	}
	
	/**
	 * @name loop
	 * @desc the loop function runs an endless traffic light.
	 *       Remember, how a traffic light goes - red, red/yellow
	 *       green, yellow. And again. 
	 */
	void loop() {
	  // switch the red light ro HIGH 
	  digitalWrite(RED, HIGH);
	  
	  // wait for a while
	  delay(1000);
	  
	  // and so on. Try the next steps.
	}

Die Wartezeiten zwischen den Farbwechseln sind unterschiedlich lang. Wie lassen sich die Intervalle variieren?

## Arrays - mehrwerte Wertelisten
Mehrere Werte können in eine Liste geschrieben werden. Dabei dienen Klammern als Notationshilfe. In den eckigen Klammern wird die Anzahl der Listeneinträge angegeben. Die geschweiften Klammern gruppieren die einzelnen Wertangaben. Sie sind jeweils durch Kommas getrennt. 

	int myInts[6];
	int myPins[] = {2, 4, 8, 3, 6};
	int mySensVals[6] = {2, 4, -8, 3, 2};
	char message[6] = "hello";

**Wertetypen für Texte und Literale**
Textwerte (strings) können auf zwei Arten notiert werden.

	char myStr1[15];
	char myStr2[8] = {'a', 'r', 'd', 'u', 'i', 'n', 'o'};
	char myStr3[8] = {'a', 'r', 'd', 'u', 'i', 'n', 'o', '\0'};
	char myStr4[ ] = "arduino";
	char myStr5[8] = "arduino";
	char myStr6[15] = "arduino";

**Funktionen**

**Gültigkeitsbereiche**

# Traffic Lights mit Listen

	/**
	 * @name Traffic Lights With Arrays
	 * @desc INTRODUCTION
	 *       Try to store the light values into list and to iterate
	 *
	 * @package Arduino Basics
	 * @author Michael <michael@zenbox.de>
	 * @since 2016/12/25
	 * @version v1.0.1
	 * @copyright (c) 2017 Michael Reichart GmbH, Cologne
	 * @license MIT License [https://opensource.org/licenses/MIT]
	 */
	
	// declare the pins
	const int RED    = 3;
	const int YELLOW = 5;
	const int GREEN  = 6;
	
	/**
	 * @desc store the number of leds. Because it is used to iterate,
	 *       it must be defined as a 'const'.
	 */
	const int NUM_LED = 3;
	
	/**
	 * @desc The list of pins as an array.
	 *       it must be defined as a 'const'.
	 */
	int ledPins[NUM_LED] = { RED, YELLOW, GREEN };
	
	// Ampelsteuerung
	const int NUM_STATES = 4;
	int redStates[NUM_STATES]    = {LOW,  LOW,  HIGH, HIGH};
	int yellowStates[NUM_STATES] = {LOW,  HIGH, LOW,  HIGH};
	int greenStates[NUM_STATES]  = {HIGH, LOW,  LOW,  LOW};
	
	int wait = 1000;
	
	/* @name setup()
	 * @desc the setup function runs once when the board is started by
	 *       pressing you reset or empower the board. While setting up,
	 *       pins and serial can be configured.
	 */
	void setup() {
	  // Anfangszustand eins Pins
	  // Über eine Schleife alle LEDs steuern
	  for (int i = 0; i < NUM_LED; i = i + 1 ) {
	    pinMode(ledPins[i], OUTPUT);
	    digitalWrite(ledPins[i], LOW);
	  }
	}
	
	void loop() {
	  // Ampelphasen steuern
	  // i++ -> i=i+1
	  for (int i = 0; i < NUM_STATES; i++) {
	    digitalWrite(ledPins[0], redStates[i]);    // ROT
	    digitalWrite(ledPins[1], yellowStates[i]); // GELB
	    digitalWrite(ledPins[2], greenStates[i]);  // GRÜN
	    delay(wait);
	  }
	}
	3 Licher Steuerung
	{HIGH, LOW, LOW}            Ampelphase 1   o  -  -
	{HIGH, HIGH, LOW}           Ampelphase 2   o  o  -
	{LOW, LOW, HIGH}            Ampelphase 3   -  -  o
	{LOW, HIGH, LOW}            Ampelphase 4   -  o  -
	
	Jeweils einzelne Lichter steuern
							    rot  rot/gelb  grün  gelb	
	{HIGH, HIGH, LOW,  LOW}     o    o         -     -
	{LOW,  HIGH, LOW,  HIGH}    -    o         -     o
	{LOW,  LOW,  HIGH, LOW}     -    -         o     -