# Das Scaffolding Snippet in Atom einrichten

Das Arduino-Programm-Gerüst (Scaffolding) wird bei jedem Programm gebraucht. Ein in Atom hinterlegtes Codesnippet erspart einem das wiederholte Tippen und stellt den Code über eine Abkürzung, zum Beispiel `ino` zur Verfügung. Ein Snippet wird so eingerichtet:

1. Öffnen der Snippets (File Menü -\> Snippets ).
2. Am Ende der Datei den Snippetcode einfügen.
3. Speichern.

Das Snippet ist in Coffeescript notiert und entspricht einer JSON Syntax ohne die Verwendung von Kommas oder Strichpunkten. Die Hierarchie wird über Einrückungen und Zeilenumbrüche erzeugt.
Die Struktur eines Snippets ist:
	'source.cpp'                <- Sprachsektion
	  'Arduino Scaffolding':    <- Name des Snippets
	    'prefix': 'ino'         <- Das Kürzel für das Snippet
	    'body': """
	    der Code in
	    vielen Zeilen
	    """
	  'Another Snippet':
	    'prefix': 'another'
	    'body': 'another code snippet for $1'

Für die geführte Eingabe von Werten, zum Beispiel dem Programmnamen im Docblock-Kommentar werden Platzhalter `$1, $2` im Snippetcode eingefügt. Der Cursor springt nach dem Einfügen des Snippetscodes automatisch dorthin.

Weitere Snippets lassen sich einfach anhängen. Es darf übrigens für jede Sprache nur eine Sektion eingerichtet werden. 
	'.text.html':
	  ...
	''.source.js':'
	  ...
	 '.source.cpp':
	  ...
	

## Das Snippet für Arduino
	# - - - - - - - - - -
	# ARDUINO SNIPPETS
	# - - - - - - - - - -
	'.source.cpp':
	# - - - - - - - - - -
	# THE ARDUINO SCAFFOLDING
	# - - - - - - - - - -
	    'Arduino Scaffolding':
	        'prefix': 'ino'
	        'body': """
	        #include <Arduino.h>
	
	        /**
	         * @name $1
	         * @desc $2 [use the tab key to step forward ...]
	         *
	         * @package Arduino Basics
	         * @author Michael <michael@zenbox.de>
	         * @since 2017/01/05
	         * @version v1.0.0
	         * @copyright (c) 2017 Michael Reichart
	         * @license MIT License <http://opensource.org/licenses/MIT>
	         */
	
	         // declare a pin for the onboard led
	         const byte PIN = 13;
	
	         void setup() {
	           // init a serial port
	           Serial.begin(9600);
	           Serial.print("Everything seems fine ...");
	
	           // init the led pin
	           pinMode(PIN, OUTPUT);
	           digitalWrite(PIN, LOW);
	         }
	
	         void loop() {
	           // blink
	           digitalWrite(PIN, HIGH);
	           delay(500);
	           digitalWrite(PIN, LOW);
	           delay(500);
	         }
	        """
	