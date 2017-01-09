# Arduino - Schritt für Schritt einrichten
- USB-Kabel anschließen
- Auf Windows in der Hardwareliste konfigurieren
- Arduino Software öffnen
- Port einstellen

# Arduino für Windows konfigurieren

## Die Arduino IDE installieren
1. IDE von [http://arduino.cc/en/Main/Software](http://arduino.cc/en/Main/Software) herunterladen und installieren.
2. Arduino.exe starten.
3. Treiber für die IDE-Board Kommunikation  installieren. 

## Treiber unter Windows installieren
1. »Neue Hardware«-Assistent erscheint nach dem anschließen. 
2. Versucht automatisch, den Treiber zu suchen und installieren. Der Versuch schlägt fehl.
3. Startmenü -\> Systemsteuerung -\> System und Sicherheit. Gerätemanager.
4. Eintrag in COM und LPT namens Arduino UNO wählen und Treibersoftware aktualisieren.  
	Treiber aus Arduino-Ordner verwenden (Arduino-UNO.inf). 

## Das Arduino Board einrichten
1. Board über USB-Port mit Computer verbinden.
2. Leuchtet die grüne Betriebs-LED?
3. Orangefarbene LED (Pin 13 LED) geht an/aus?
4. Das Board funktioniert!

## Das Board funktioniert nicht?
- Kein Strom?
- kein Standardboard?
- Defekt?
- mehr unter [http://arduino.cc/en/Guide/Windows](http://arduino.cc/en/Guide/Windows) für Windows, [http://arduino.cc/en/Guide/MacOSX](http://arduino.cc/en/Guide/MacOSX)für Mac OS X und [http://www.arduino.cc/playground/Learning/Linux](http://www.arduino.cc/playground/Learning/Linux) 

# Die Inbetriebnahme des Arduino Uno
Im Sketcheditor betrachten und editieren Sie den Code eines Sketches. 

1. IDE starten.
2. File -\> Examples -\> Basics -\> Blink auswählen und öffnen.
3. Code erscheint im Sketch-Editor.
4. Code kompilieren (Button oben links mit Häkchen)
5. ￼Nachrichtenbereich: `»Compiling sketch...«, ... dann »Done Compiling. Binary sketch size: 1026 bytes (of a 32256 byte maximum)«`

![](DraggedImage.png)

## Fehler beim Kompilieren und Upload
- kompilierte Sketch ist größer als verfügbare Speicher? `Sketch too big; see http://www.arduino.cc/en/Guide/Troubleshooting#size for tips on reducing it.`  
	Lösung: Sketch kürzen oder Board mit höherer Kapazität. 
- Fehler im Code?  
	Lösung: Fehlermeldung lesen und Fehler beheben, erneut kompilieren.

## Der Upload
1. IDE -\> Tools -\> Board: Namen des angeschlossenen Boards auswählen.
2. IDE -\> Tools -\> Serial Port: USB Anschluss oder COM Schnittstelle (vermutlich der letze Eintrag) auswählen.
3. Upload-Button Klicken.
---- 
- Der Code wird kompiliert und hochgeladen.
- Solange flackern die beiden "Seriell"-LEDs.
- Dann fängt die ursprüngliche LED wieder an zu blinken. 

# Das Blink Skript

	/*
	  Blink
	  Turns on an LED on for one second, then off for one second, repeatedly.
	*/
	
	
	// Die Setup Funktion wird einmal ausgeführt - 
	// bei der Inbetriebnahme des Boards oder nach Drücken des Reset-Schalters.
	void setup() {
	  // Der Digitalpin 13 wird als Ausgabepin definiert
	  pinMode(13, OUTPUT);
	}
	
	// Die Loop Funktion läuft nach dem Setup und wiederholt sich endlos, 
	// solange das Boards Strom hat.
	void loop() {
	  digitalWrite(13, HIGH);   // Die LED wird angeschaltet (Pin 13 auf HIGH),
	  delay(1000);              // wartet eine Sekunde,
	  digitalWrite(13, LOW);    // schaltet die LED ab (LOW),
	  delay(1000);              // wartet eine Sekune
	}