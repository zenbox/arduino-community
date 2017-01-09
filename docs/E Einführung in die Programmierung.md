# Struktur eines Arduino Programms
Der Aufbau eines Arduino Programmes gliedert sich in zunächst zwei Teile, Funktionen genannt. Die beiden Funktionen umschliessen mit geschweiften Klammern  `{ }` Blöcke von Anweisungen. 

	// Deklaration einer globalen Variablen
	int pin = 13;
	
	void setup () { 
		// Anweisungen zur Ausführungsvorbereitung
	}
	
	void loop () { 
		// Anweisungen zur wiederholten Programmausführung; 
	} 

Die Funktion `setup()` führt die Programmvorbereitung aus, `loop()` die Ausführung. Beide Funktionen werden zur Programmausführung gebraucht. Noch vor der `setup(){}` Funktion werden globale Variablen deklariert. Sie stehen das Datenbehälter überall im Programm zur Verfügung.

	int pin = 13;

Setup wird nur einmal ausgeführt und dient zum Beispiel dem Setzen von `pinMode()` oder der Initiierung der seriellen Kommunikation.

	void setup () { 
		pinMode(pin, OUTPUT); // 'pin' als Ausgang definieren 
	} 

Die `loop()` Funktion beinhaltet Programmcode, der kontinuierlich in einer unendlichen Schleife ausgeführt wird - Eingänge auslesen, Ausgänge triggern, Daten verarbeiten. 

	void loop() { 
		digitalWrite(pin, HIGH); // schaltet 'pin' ein 
		delay(1000); // Pause für eine Sekunde 
		digitalWrite(pin, LOW); // schaltet 'pin' aus 
		delay(1000); // Pause für eine Sekunde 
	}

## Funktionen 
Eine Funktion ist ein Block von Anweisungen mit einem Namen. Es gibt sowohl fertige Funktionen der Arduino IDE (wie `void setup ()` und `void loop()`). Es können aber auch eigene Funktionen entwickelt werden.

	void blink (int pin) {
		digitalWrite(pin, HIGH); // schaltet 'pin' ein 
		delay(1000);             // Pause für eine Sekunde 
		digitalWrite(pin, LOW);  // schaltet 'pin' aus 
		delay(1000);             // Pause für eine Sekunde 
	}

Funktionen haben den Vorteil, dass sie wiederverwendet werden können.

	void loop () {
		blink(13);
		blink(13);
		blink(13);
	}

### Aufbau einer Funktion
	type functionName (type param_1, type param_2) { 
		type result = do something more complex; 
		return result;
	} 

	int addTwoNumbers (int a, int b) { 
		int c = a + b; 
		return c;
	} 

Der Typ einer Funktion entspricht dem Datentyp eines zurückgegebenen Wertes, so wie zum Beispiel 'int' für den Integer Typen. Eine Funktion, die nichts zurückgibt, verwendet des Funktionstyp '`void`'. 

Der Typ-Angabe folgt die Festlegung des Funktionsnamens. Funktionsnamen folgen meist der sogenannten lowerCamelcase-Schreibweise, sie beginnen mit einem Kleinbuchstaben und zeigen Wortzusammensetzungen mit Grossbuchstaben an. Funktionsnamen können frei festgelegt werden. Sie sollten 'sprechend' sein, also  im Namen die Aufgabe der Funktion 'erläutern'.

Einer Funktion werden meist Parameter mitgegeben, deren Werte durch die Funktion verarbeitet werden. Auch Parameter werden 'typisiert' angegeben. 

**Parameter haben einen lokalen Scope.**

Parameter, wie auch Variablen, die innerhalb der Funktion deklariert werden sind 'lokal', das heisst, sie sind nur innerhalb der Funktion verwendbar. Ausserhalb existieren sie nicht. Die Bereichsbindung wird Gültigkeitsbereich oder engl. 'Scope' genannt.

**`{}` geschweifte Klammern **

Geschweifte Klammern definieren den Anfang und das Ende von Funktions- und Anweisungsblöcken. Sie treten immer paarweise auf. 

	typ function () { anweisungen; }

Fehler bei der Klammersetzung führen zu Fehlern in der Codeausführung. Die Arduino IDE zeigt bei Auswahl einer Klammer das damit verbundene Gegenstück an. 

**`;` Semikolon **

Ein Strichpunkt oder Semikolon kennzeichnet das Ende einer Anweisungszeile und trennt sie von der folgenden. Vergessen eines Semikolons am Ende einer Zeile führt zu einem Fehler im Kompiler. 

**`/*... */` Block Kommentare **

Block-Kommentare oder mehrzeilige Kommentare sind Textbereiche die vom Kompiler ignoriert werden. Sie dienen eigenen Notizen. Sie beginnen mit `/*` an und enden mit `*/`. Dazwischen stehen ein oder mehrere Zeilen Text. Kommentare werden vom Kompiler ignoriert und belegen keinen Speicherplat.

**`//` Einzeilige Kommentare **
Einzeilige Kommentare werden mit einem `//` am Anfang der Zeile definiert und enden mit dem Ende der Zeile. 

	// dies ist ein einzeiliger Kommentar 

Einzeilige Kommentare können auch direkt nach dem Strichpunkt einer Anweisungszeile notiert werden. 

# Variablen
Eine Variable ist die Benennung eines Platzhalters für einen numerischen oder alphanumerischen Wert. Eine Variable richtet einen Speicherplatz ein, in den im Zuge des Programmablaufes wechselnde (variable) Werte abgelegt werden.

Eine Variable muss mit Angabe ihres Wartetyps deklariert werden und kann optional mit einem Initialwert versehen werden.  

	int pin = A2;      // deklariert eine Variable und setzt ihren Wert auf A2 
	                   // A2 ist der Pinname für den Analogpin 2
	int pinValue = 0; // deklariert eine andere Variable, Wert ist 0
	
	pinValue = analogRead(pin); // setzt den Wert der Variable gleich 
	                            // mit dem Wert von Analogpin 2 

`pin` ist die Variable selber, ihr Datentyp ist `int` ist, das ist der Kurzausdruck für Integer oder Ganzzahl. Der Variablen wird der Initialwert `A2` zugewiesen. `pinValue` ist eine zweite Variable mit dem dem Initialwert 0.

Andere Wertetypen sind zum Beispiel `int`, `long`, `float` oder auch `char`.

`pinValue = analogRead(pin); ` liest die Spannungswert aus dem Analogpin 2 aus und übergibt ihn in die Variable `pinValue`.

	delay(pinValue);       // benutzt die Variable als Verzögerung 

Variablennamen sollten deutlich beschreiben, welchen Wert sie enthalten, um den Code besser lesbar zu machen. Dies hilft dem Programmierer und anderen beim Verständnis des Quelltextes. `button`, `ledPin`, `sensorValue` ...

## Konstanten sind auch Variablen

Konstanten werden allerdings nur einmal mit einem Wert belegt. Dieser Wert lässt sich im weiteren Programmablauf nicht mehr ändern.

	const int pin = A2;

Ansonsten gelten für Konstanten dieselben Regeln, wie für Variablen. Um eine Konstante besser erkennbar zu machen, werden deren Namen oft in Großbuchstaben notiert.

	const int PIN = A2;

### Geltungsbereich einer Variablen

Eine Variable kann fast überall im Programm deklariert werden. Der Ort der Deklaration bestimmt, welche Programmteile Zugriff auf die Variable haben.

Mögliche Orte für eine Variablendeklaration sind der Programmanfang vor der `setup` Funktion. Hier ist eine Variable global, gültig. Am Anfang einer Funktion oder auch innerhalb einer Kontrollstruktur, wie einer Schleife, deklariert, ist eine Variable nur lokal gültig.

Eine globale Variable kann von jeder Funktion und Anweisung des Programmes gesehen und benutzt werden. Eine lokale Variable ist nur sichtbar und nutzbar innerhalb der Funktion oder Struktur, in der sie deklariert wurde. 

	int value; // 'value' ist sichtbar 
	          // für jede Funktion 
	
	void setup() { ... } 
	void loop() { 
		for (int i=0; i<20; i++) { // 'i' ist nur sichtbar 
	                               // innerhalb der for-Schleife 
			float f; // 'f' ist nur sichtbar 
		} // innerhalb der for-Schleife
	}

# Datentypen 
## byte 
Byte speichert einen 8-bit numerischen, ganzzahligen Wert ohne Dezimalkomma. Der Wert kann zwischen 0 und 255 sein. Wird ein Wert größer als 255 gespeichert, dann "läuft das Register über" -  es fängt wieder bei Null an. Dies gilt für die meisten Zahlentypen.

	byte someVariable = 180; // deklariert 'someVariable' 
	                         // als einen 'byte' Datentyp 

## int 
Integer sind der verbreitetste Datentyp für die Speicherung von ganzzahligen Werten ohne Dezimalkomma. Sein Wert hat 16 Bit und reicht von -32.767 bis 32.768. 

	int someVariable = 1500; // deklariert 'someVariable' 
	                         // als einen 'integer' Datentyp 

Auch Integer Variablen werden bei Überschreiten der Limits 'überrollen'. Zum Beispiel wenn `x = 32767` und eine Anweisung addiert 1 zu x, `x = x + 1` oder `x++`, wird 'x' dabei 'überrollen' und den Wert -32,768 annehmen. 

## long 
Datentyp für lange Integer mit erweiterter Größe, ohne Dezimalkomma, gespeichert in einem 32-bit Wert in einem Spektrum von -2,147,483,648 bis 2,147,483,647. 

	long someVariable = 90000; // deklariert 'someVariable' 
	                           // als einen 'long' Datentyp 

## float 
Ein Datentyp für Fliesskommawerte oder Nummern mit Nachkommastellen. Fliesskomma zahlen haben eine bessere Auflösung als Integer und werden als 32-bit Wert mit einem Spektrum von -3.4028235E+38 bis 3.4028235E+38 angelegt.

	float someVariable = 3.14; // deklariert 'someVariable' 
	                           // als einen 'float' Datentyp 

Fliesskommazahlen sind allerdings nicht präzise und führen möglicherweise zu merkwürdigen Resultaten, wenn sie verglichen werden. Ausserdem sind Fliesskommaberechnungen langsamer als Integerberechnungen. 

## array 
Ein Array ist eine Werteliste. Die Liste der Werte wird mit geschweiften Klammern begrenzt, die Werte selbst durch Kommata getrennt.

	int myArray[] = {wert0, wert1, wert2...} 

Jeder Wert in einem Array kann über einen numerischen Index aufgerufen werden. Der Index eines Arrays fängt bei 0 an. Ein Array muss deklariert werden und optional mit Werten belegt werden, bevor es genutzt werden kann. 

Genau so ist es möglich ein Array zuerst mit Datentyp und Größe zu deklarieren und später einer Index Position einen Wert zu geben. 

	int myArray[5];  // deklariert Datentyp 'integer' als Array mit 6 Positionen 
	myArray[3] = 10; // gibt dem 4. Index den Wert 10 

Um den Wert eines Arrays auszulesen, kann man diesen einfach einer Variablen mit Angabe des Arrays und der Indexposition zuordnen. 

	x = myArray[3]; // x hat nun den Wert 10 

Arrays werden oft für Schleifen verwendet, bei denen der Zähler der Schleife auch als Index Position für die Werte im Array verwendet wird. Das folgende Beispiel nutzt ein Array um eine LED zum flackern zu bringen. Mit einer for-Schleife und einem bei 0 anfangenden Zähler wird eine Indexposition im Array ausgelesen, an den LED-Pin gesendet, eine 200ms Pause eingelegt und dann dasselbe mit der nächsten Indexposition durchgeführt. 

	int ledPin = 10; // LED auf Pin 10 
	byte flacker[] = {180, 30, 255, 200, 10, 90, 150, 60}; // Array mit 8 verschiedenen Werten 
	
	void setup() { 
		pinMode(ledPin, OUTPUT); // Setzt den OUTPUT Pin 
	} 
	
	void loop() { 
		for(int i=0; i<7; i++) { // Schleife gleicht der Anzahl
	                             // der Werte im Array
			analogWrite(ledPin, flacker\[i]); // schreibt den Indexwert auf die LED
			delay(200); // 200ms Pause 
		} 
	} 


# Arithmetik 
Arithmetische Operatoren umfassen Addition, Subtraktion, Multiplikation und Division. Sie geben die Summe, Differenz, das Produkt oder den Quotienten zweier Operatoren zurück. 

	y = y + 3; 
	x = x - 7; 
	i = j \* 6; 
	r = r / 5; 

Die Operation wird unter Beibehaltung der Datentypen durchgeführt. `9 / 4` wird so zum Beipiel zu `2` und nicht `2.25`, da `9` und `4` Integer sind und keine Nachkommastellen unterstützen. Dies bedeutet auch, dass die Operation überlaufen kann, wenn das Resultat größer ist, als es der Datentyp zulässt. Wenn die Operanden unterschiedliche Datentypen haben wird der größere Typ verwendet. Hat zum Beispiel eine der Nummern (Operanden) den Datentyp `float` und der andere `int`, so wird Fliesskomma-Mathematik zur Berechnung verwendet. 

Bemerkung: Wähle variable Größen, die groß genug sind um die Werte der Ergebnisse zu speichern. Sei Dir bewusst an welcher Stelle die Werte überlaufen und auch was in der Gegenrichtung passiert. z.B. bei (0 - 1) oder (0 - -32768). Für Berechnungen, die Brüche ergeben, sollten immer `float`-Variablen genutzt werden. Allerdings mit dem Bewusstsein der Nachteile: Großer Speicherbedarf und langsame Geschwindigkeit der Berechnungen. Nutze den Form-Operator z.B. `(int) myFloat`, um einen Variablentypen spontan in einen anderen zu verwandeln. Zum Beispiel wird mit `i = (int) 3.6` die Variable `i` auf den Wert `3` gesetzt. 

## Gemischte Zuweisungen 
Gemischte Zuweisungen kombinieren eine arithmetische Operation mit einer Variablenzuweisung. Diese werden üblicherweise in Schleifen gefunden, die wir später noch genau Beschreiben wird. Die gängigsten gemischten Zuweisungen umfassen: 

	x++    // identisch mit x = x + 1, oder Erhöhung von x um +1 
	x--    // identisch mit x = x - 1, oder Verminderung von x um -1 
	x += y // identisch mit x = x + y, oder Erhöhung von x um +y 
	x -= y // identisch mit x = x - y, oder Verminderung von x um -y 
	x *= y // identisch mit x = x \* y, oder Multiplikation von x mit y 
	x /= y // identisch mit x = x / y, oder Division von x mit y 

Bemerkung: Zum Beispiel führt `x *= 3` zur Verdreifachung des alten Wertes von `x`und weist der Variablen `x` des Ergebnis der Kalkulation zu. 

## Vergleichende Operatoren 
Der Vergleich von Variablen oder Konstanten gegeneinander wird oft in `if`-Anweisungen durchgeführt, um bestimmte Bedingungen auf Wahrheit zu testen: 

	x == y // x ist gleich wie y 
	x != y // x ist nicht gleich wie y 
	x < y // x ist weniger als y 
	x > y // x ist mehr als y 
	x <= y // x ist weniger oder gleich wie y 
	x >= y // x ist größer oder gleich wie y 

## Logische Operatoren 
Logische Operatoren sind eine Methode, um zwei Ausdrücke zu vergleichen und ein ``true```oder `false`, je nach Operator, zurück zu liefern. Es gibt drei logische Operatoren `AND`, `OR` und `NOT`, die oft in `if`-Anweisungen verwendet werden:

Logisch AND: 
	if (x > 0 && x < 5) // nur WAHR wenn beide 
	                    // Ausdrücke WAHR sind

Logisch OR: 
	if (x > 0 \|| y > 0) // WAHR wenn einer der 
	                     // Ausdrücke WAHR ist 

Logisch NOT: 
	if (!x > 0) // nur WAHR wenn der 
	            // Ausdruck FALSCH ist 


# Vordefinierte Konstanten 
Die Arduino Programmiersprache hat ein paar vordefinierte Werte, die man auch Konstanten nennt. Sie machen den Programmcode einfacher lesbar. Konstanten werden in Gruppen unterteilt. 

## `true`/`false` 
Diese sind Boolsche Konstanten, die logische Level definieren. `false` ist einfach als `0` (Null) definiert, während `true` oft als 1 definiert wird. Es kann aber alles ausser Null sein. Im Sinne von Boolean ist auch `-1,2` und `-200` als `true` definiert. 

	if (b == TRUE); { 
		machEtwas; 
	} 

## `HIGH`/`LOW` 
Diese Konstanten definieren Pinlevel als `HIGH` oder `LOW` und werden beim Lesen oder Schreiben auf digitalen Pins verwendet. `HIGH` ist als Logiklevel 1, ON oder 5 Volt definiert, während `LOW` als Logiklevel 0, OFF oder 0 Volt definiert ist. 

	digitalWrite(13, HIGH); 

## `INPUT`/`OUTPUT` 
Konstanten, die in der `pinMode()` Funktion benutzt werden und einen digitalen Pin entweder als `INPUT` oder `OUTPUT` definieren. 

	pinMode(13, OUTPUT); 

# Ablaufsteuerung 
## `if` 
Die `if`-Abfrage testet, ob eine bestimmte Bedingung wahr ist oder nicht. Bei einem analogen Wert kann dies das Erreichen eines bestimmten Levels sein. Ist dies der Fall, so werden Anweisungen innerhalb der geschweiften Klammer ausgeführt. Ist diese Bedingung nicht erfüllt, werden die Anweisungen innerhalb der Klammer übersprungen. Das Format für eine `if`-Abfrage ist folgendes: 
	if (someVariable == value) { 
		doSomething; 
	} 

Das oben vorgestellte Beispiel vergleicht `someVariable`mit einem anderen Wert `value`, der entweder eine Variable oder Konstante sein kann. Wenn der Vergleich oder die Bedingung wahr ist werden die Anweisungen innerhalb der Klammern ausgeführt, in diesem Beispiel `doSomething`. Wenn nicht, wird der Teil übersprungen und es geht nach den Klammern weiter in der Ausführung des Programmcodes. 

Bemerkung: Vorsicht vor dem versehentlichen Verwenden von `=`, wie in `if (x=10)`. Technisch gesehen wird hier die Variable `x` mit dem Wert `10` belegt, was immer wahr ist. Anstatt dessen nutze `==`, wie in `if (x==10)`. Hierbei wird nur geprüft ob `x` den Wert `10` hat oder nicht. Am einfachsten merkt man sich das mit `=` als 'gleich' im Gegensatz zu `==` als 'ist gleich mit'. 

## `if ... else` 
`if ... else` erlaubt das Treffen einer 'entweder ... oder' Entscheidung. Zum Beispiel möchten Sie einen digitalen Eingang prüfen und im Falle von `HIGH` andere Anweisungen ausführen, als im Falle von `LOW`. Dies kann man so im Programmcode abbilden: 

	if (inputPin == HIGH) { 
		doThingA; 
	} else { 
		doThingB; 
	} 

`else` kann auch noch weitere `if`-Abfragen enthalten, so dass mehrfache Test zur selben Zeit stattfinden können. Es ist sogar möglich, eine unbegrenzte Anzahl von diesen `else` Abzweigungen zu nutzen. Allerdings wird je nach den Bedingungen nur ein Set von Anweisungen ausgeführt: 

	if (inputPin < 500) { 
		doThingA; 
	} else if (inputPin >= 1000) { 
		doThingB; 
	} else { 
		doThingC; 
	}

Bemerkung: Eine `if`-Abfrage testet, ob eine Bedingung innerhalb der Klammer wahr oder falsch ist. Diese Bedingung kann jedes gültige `C`-Statement sein, wie in unserem ersten Beispiel `if (inputPin == HIGH)`. In diesem Beispiel prüft die `if`-Abfrage nur, ob der definierte Eingang den Logiklevel `HIGH` hat (+5 Volt).

## `for` 
Die `for`-Schleife wird verwendet, um einen Block von Anweisungen in geschweiften Klammern eine festgelegt Anzahl von Wiederholungen durchlaufen zu lassen. Ein Erhöhungzähler wird oft verwendet, um die Schleife zu ansteigen zu lassen und zu beenden. Es gibt im Header der `for`-Schleife drei Elemente, getrennt durch Semikolon `;`. 

	for (Initialisierung; Bedingung; Ausdruck) { 
		doSomething; 
	} 

Die Initialisierung einer lokalen Variablen, einem ansteigenden Zähler, passiert als erstes und nur einmalig. Bei jedem Durchlaufen der Schleife wird die Bedingung an der zweiten Stelle getestet. Wenn die Bedingung wahr ist, läuft die Schleife weiter und die folgenden Ausdrücke und Anweisungen werden ausgeführt und die Bedingung wird erneut überprüft. Ist die Bedingung nicht mehr wahr, so endet die Schleife. Das folgende Beispiel startet mit einem Integer Wert `i` bei `0`, die Bedingung testet, ob der Wert noch kleiner als `20` ist und wenn dies wahr ist so wird `i` um einen Wert erhöht und die Anweisungen innerhalb der geschweiften Klammern werden ausgeführt: 

	for (int i=0; i<20; i++) {      // deklariert 'i', teste ob weniger
	                                // als 20, Erhoehung um 1 
		digitalWrite(13, HIGH); // schaltet Pin 13 ein 
		delay(250);             // Pause fuer 1/4 Sekunde 
		digitalWrite(13, LOW);  // schaltet Pin 13 aus 
		delay(250);             // Pause fuer 1/4 Sekunde 
	} 

Bemerkung: Die `for`-Schleife in der Programmiersprache `C` ist viel flexibler als in einigen anderen Programmiersprachen, inklusive Basic. Jede oder alle der drei Header Elemente können weggelassen werden, jedoch sind die Semikolons notwendig. Zusätzlich können die Statements für Initialisierung, Bedingung und Ausdruck durch jedes gültige `C` Statement mit Variablen ohne Bezug zur Schleife ersetzt werden. Diese Methode kann Lösungen für seltene Probleme beim Programmieren bieten. 

## `while` 
`while` Schleifen werden unbegrenzt wiederholt und laufen unendlich, bis eine bestimmte Bedingung innerhalb der Klammer falsch ist. Etwas muss die zu testende Variable ändern oder die Schleife endet nie. Dies kann im Code passieren, wie eine ansteigende Variable oder von externen Werten, wie einem Sensor Test erfolgen. 

	while (someVariable != value) { 
		doSomething; 
	} 

Das folgende Beispiel testet ob `someVariable` weniger als 200 ist. Die Anweisungen innerhalb der Schleife werden ausgeführt, solange bis `someVariable` nicht mehr weniger als 200 ist. 

	while (someVariable < 200) { // testet ob weniger als 200
		doSomething;         // führt Anweisungen aus 
		someVariable++;      // erhöht Variable um 1 
	} 

## `do... while` 
Die `do...while` Schleife ist eine endgesteuerte Schleife, die ähnlich funktioniert wie die `while` Schleife. Der Unterschied ist der Test der Bedingung am Ende der Schleife. Somit läuft die Schleife immer mindestens einmal. 

	do { 
		doSomething; 
	} while (someVariable != value); 

Das folgende Beispiel ordnet `readSensors()` der Variablen `x` zu, macht eine Pause für 50ms, um dann unbegrenzt weiter zu laufen, bis `x` nicht mehr weniger als 100 ist. 

	do { 
		x = readSensors();  // ordnet den Wert von 
		                    // readSensors() 'x' zu 
			delay (50); // Pause für 50ms 
	} while (x < 100); // Schleife laeuft weiter bis 'x' weniger als 100 ist 

# Digitaler Input - Output 
## pinMode(pin,mode) 
Wird in `void setup()` benutzt, um einen speziellen Pin entweder als Eingang oder Ausgang zu konfigurieren. 

	pinMode(pin, OUTPUT); // setzt ‘pin’ als Ausgang

Arduinos digitale Pins sind standardmäßig Eingänge, weshalb sie nicht extra als Eingänge mit `pinMode()` festgelegt werden müssen. Als Eingang konfigurierte Pins haben einen Zustand hoher Impendanz. Es gibt im ATmega Chip auch komfortable 20 k Pullup Widerstände, die per Software zugängig sind. Auf diese eingebauten Pullup Widerstände kann in folgender Weise zugegriffen werden: 

	pinMode(pin, INPUT); // setzt ‘pin’ als Eingang digitalWrite(pin, HIGH); // schaltet den 'Pullup' Widerstand ein 

Pullup Widerstände werden normalerweise verwendet, um Eingänge wie Schalter anzuschliessen. In dem vorgestellten Beispiel fällt auf, dass der Pin nicht als Ausgang definiert wird, obwohl auf ihn geschrieben wird. Es ist lediglich die Methode, den internen Pullup Widerstand zu aktivieren. Als Ausgang konfigurierte Pins sind in einem Zustand geringer Impendanz und können mit maximal 40 mAmpere Strom von angeschlossenen Elementen und Schaltkreisen belastet werden. Dies ist genug um eine LED aufleuchten zu lassen (seriellen Widerstand nicht vergessen), aber nicht genug um die meisten Relais, Magnetspulen oder Motoren zu betreiben. Kurzschlüsse an den Arduino Pins, genau wie zu hohe Stromstärken, können den Output Pin oder gar den ganzen ATmega Chip zerstören. Aus dem Grund ist es eine gute Idee einen Ausgangspin mit externen Elementen in Serie mit einem 470 oder 1K Widerstand zu schalten. 

## digitalRead(pin) 
`digitalRead(pin)` liest den Wert von einem festgelegten digitalen Pin aus, mit dem Resultat entweder `HIGH` oder `LOW`. Der Pin kann entweder als Variable oder Konstante festgelegt werden (0-13). 

	value = digitalRead(Pin); // setzt 'value' gleich mit 
				  // dem Eingangspin 

## digitalWrite(pin,value) 
Gibt entweder den Logiklevel `HIGH` oder `LOW` an einem festgelegten Pin aus. Der Pin kann als Variable oder Konstante festgelegt werden (0-13). 

	digitalWrite(pin, HIGH); // setzt 'pin' auf high (an)

Das folgende Beispiel liest einen Taster an einem digitalen Eingang aus und schaltet eine LED ein, wenn der Taster gedrückt wird: 

	int led = 13;  // LED an Pin 13 angeschlossen 
	int pin = 7;   // Taster an Pin 7 angeschlossen 
	int value = 0; // Variable um den Auslesewert zu speichern
	 
	void setup() { 
		pinMode(led, OUTPUT); // legt Pin 13 als Ausgang fest 
		pinMode(pin, INPUT);  // legt Pin 7 als Eingang fest 
	}
	 
	void loop() { 
		value = digitalRead(pin); // setzt 'value' gleich mit 
		                          // dem Eingangspin 
		digitalWrite(led, value); // setzt 'led' gleich mit dem } 
		                          // Wert des Tasters 

# Analoger Input - Output 
## `analogRead(pin)` 
Liest den Wert eines festgelegten analogen Pins mit einer 10 Bit Auflösung aus. Diese Funktion ist nur für Pins (0-5) verfügbar. Die resultierenden Integer Werte haben ein Spektrum von 0 bis 1023. 

	value = analogRead(pin); // setzt 'value' gleich mit 'pin' 

Bemerkung: Analoge Pins müssen im Gegensatz zu digitalen nicht zuerst als Eingang oder Ausgang deklariert werden. 

## `analogWrite(pin, value)` 
Schreibt pseudo-analoge Werte mittels einer hardwarebasierten Pulsweitenmodulation (PWM) an einen Ausgangspin. Auf neueren Arduino Boards mit dem ATmega 168 Chip ist diese Funktion für die Pins 3, 5, 6, 9, 10 und 11 anwendbar. Ältere Arduinos mit dem ATmega8 unterstützen nur die Pins 9,10 und 11. Der Wert kann als Variable oder Konstante Bereich 0-255 festgelegt werden. 

	analogWrite(pin, value); // schreibt 'value' auf den analogen 'pin' 

Ein Wert 0 generiert eine gleichmäßige Spannung von 0 Volt an einem festgelegten Pin. Ein Wert von 255 generiert eine gleichmäßige Spannung von 5 Volt an einen festgelegten Pin. Für Werte zwischen 0 und 255 wechselt der Pin sehr schnell zwischen 0 und 5 Volt - je höher der Wert, desto länger ist der Pin `HIGH` (5 Volt). Bei einem Wert von 64 ist der Pin zu drei Vierteln der Zeit auf 0 Volt und zu einem Viertel auf 5 Volt. Ein Wert von 128 führt dazu, dass die Ausgangsspannung zur Hälfte der Zeit auf `HIGH` steht und zur anderen Hälfte auf `LOW`. Bei 192 misst die Spannung am Pin zu einer Viertel der Zeit 0 Volt und zu drei Vierteln die vollen 5 Volt. Weil es eine hardwarebasierte Funktion ist, läuft die konstante Welle unabhängig vom Programm bis zur nächsten Änderung des Zustandes per `analogWrite()` (bzw. einem Aufruf von `digitalRead()` oder `digitalWrite()` am selben Pin). 

Bemerkung: Analoge Pins müssen im Gegensatz zu digitalen Pins nicht zuvor als Eingang oder Ausgang deklariert werden. Das folgenden Beispiel liest einen analogen Wert von 'pin', rechnet den Wert per Division durch 4 um und gibt ihn dann als PWM Signal an 'led'aus. 

	int led = 10; // LED mit 220 Widerstand an Pin 10 
	int pin = 0;  // Potentiometer am analogen Pin 0 
	int value;    // Wert fuer Auslesung 
	
	void setup(){} // kein Setup benoetigt
	 
	void loop() { 
		value = analogRead(pin); // setzt 'value' gleich mit 'pin' 
		value /= 4; // wandelt 0-1023 in 0-255 um 
		analogWrite(led, value); // gibt das PWM Signal an 'led' aus 
	}
![](DraggedImage.png)

# Zeit 
## delay(ms) 
Pausiert ein Programm für die Dauer der Zeit angegeben in Millisekunden, wobei 1000 = 1 Sekunde ist. 

	delay(1000); // wartet für eine Sekunde 

## millis() 
Gibt den Wert in Millisekunden als `long` Datentyp zurück, berechnet seit dem Start des aktuellen Programms. 

	value = millis(); // setzt 'value' gleich mit millis() 

Bemerkung: Dieser Wert wird nach etwa 9 Stunden überlaufen und wieder bei Null anfangen.

# Mathematisch 
## min(x, y) 
Berechnet das Minimum von zwei Werten irgend eines Datentypes und gibt den kleineren Wert zurück. 

	value = min(value, 100); // setzt 'value' als kleineren 
	                         // Wert oder 100 fest, damit 'value' 
	                         // nie größer als 100 ist. 

## max(x, y) 
Berechnet das Maximum von zwei Werten irgendeines Datentypes und gibt den höheren Wert zurück. 

	value = max(value, 100); // setzt 'value' als größeren 
	                         // Wert oder 100 fest, damit 'value' 
	                         // mindestens 100 ist. 

# Zufallsfunktionen 
## randomSeed(seed) 
Setzt einen Wert oder 'Seed'als Ausgangspunkt für die random() Funktion. 

	randomSeed(value); // setzt 'value' als den Zufalls Seed 

Der Arduino ist selber nicht in der Lage eine wirklich Zufallswerte zu produzieren. Mit `randomSeed()` kann eine Variable als `seed` verwendet werden, um bessere Zufallsergebnisse zu erhalten. Als `seed` Variable oder auch Funktion können so zum Beispiel `millis()` oder `analogRead()` eingesetzt werden, um elektrisches Rauschen durch den Analogpin als Ausgang für Zufallswerte zu nutzen. 

## random(min, max) 
Die random Funktion erlaubt die Erzeugung der pseudo-zufälligen Werte innerhalb eines definierten Bereiches von minimum und maxium Werten. 

	value = random(100, 200); // setzt 'value' mit einer Zufallszahl 
	                          // zwischen 100 und 200 gleich 

Bemerkung: Benutze dieses nach der `randomSeed()` Funktion. 

Das folgende Beispiel erzeugt einen Zufallswert zwischen 0 und 255 und gibt ihn als PWM Signal auf einem PWM Pin aus. 

	int randNumber; // Variable um den Zufallswert zu speichern 
	int led = 10;   // LED mit 220 Ohm Widerstand an Pin 10 
	
	void setup() {} // kein Setup notwendig
	
	void loop() { 
		randomSeed(millis()); // verwendet millis() als seed 
		randNumber = random(255); // Zufallsnummer im Bereich von 0-255 
		analogWrite(led, randNumber); // PWM Signal als Output 
		delay(500); // halbe Sekunde Pause 
	} 

# Die serielle Schnittstelle

Die Serielle Kommunikation wird zum Austausch von Daten zwischen den Arduino und anderen Geräten benutzt. Der serielle Port, auch bekannt als UART, USART kommuniziert über die digitalen Pins 0 (RX) und 1 (TX). RX steht für Receiver exchange und bezeichnet den Empfangspin, TX für Transmitter exchange. Über diesen Pin werden Daten gesendet. Wenn die beiden Pins zur seriellen Kommunikation genutzt werden, stehen sie als digitale Pins nicht für andere Zwecke zur Verfügung.
Die serielle Kommunikation funktioniert auch über USB mit dem Computer.

Um zwei Geräte miteinander zu verbinden, werden jeweils der TX des einen Geräts mit dem RX des anderen Gerätes verbunden und vice versa. Die serielle Kommunikation über die beiden Pins TX/RX nutzt TTL Logic Level (Transistor-Transistor-Logik) auf 5V/3V Basis (je nach Board). Daher ist auf die richtige Spannung zu achten.


## die Befehle der seriellen Schnittstelle
	if (Serial)
	available()
	availableForWrite()
	begin()
	end()
	find()
	findUntil()
	flush()
	parseFloat() - Serial.parseFloat() returns the first valid floating point number from the Serial buffer.
	parseInt() - Looks for the next valid integer in the incoming serial stream.
	peek()
	print()
	println()
	read()
	readBytes()
	readBytesUntil()
	readString()
	readStringUntil()
	setTimeout()
	write()
	serialEvent()

**Einen ASCII String über die serielle Schnittstelle**

	// setup
	Serial.begin(9600);
	
	// loop 
	while (Serial.available() > 0) {
	  if (Serial.read() == '\n') {
	
	    int red = Serial.parseInt();
	    int green = Serial.parseInt();
	    int blue = Serial.parseInt();
	
	    Serial.print(red, HEX);
	    Serial.print(green, HEX);
	    Serial.println(blue, HEX);
	  }
	}

# Die Befehle der serielle Kommunikation 
## Serial.begin(rate) 
`Serial.begin(rate)`
Öffnet den seriellen Port und setzt die Baudrate (Datenrate) für die serielle Übertragung fest. Die typische Baud Rate mit dem Computer ist 9600 Baud. Andere Geschwindigkeiten werden auch unterstützt. 

	void setup() { 
		Serial.begin(9600); // oeffnet seriellen Port 
	} // setzt die Datenrate auf 9600 bps 

Bemerkung: Wenn eine serielle Kommunikation verwendet, so können die digitalen Pins 0 (RX) und 1 (TX) nicht zur selben Zeit verwendet werden. 

## Serial.println(data) 
Schreibt Daten z, um seriellen Port, gefolgt von einem automatischen Zeilenumbruch als Carrier Return und Linefeed. Dieser Befehl hat die selbe Form wie `Serial.print()`, ist aber einfacher auf dem seriellen Monitor zu lesen. 

	Serial.println(analogValue); // sendet den Wert von 
	                             // 'analogValue'

Bemerkung: Detailiertere Informationen über die zahlreichen Varianten der `Serial.println()` und `Serial.print()` Funktionen finden Sie auf der Arduino Website. 

Das folgende einfache Beispiel liest einen Wert vom analogen Pin 0 aus und sendet die Daten an den Computer einmal pro Sekunde. 

	void setup() { 
		Serial.begin(9600); // setzt die Datenrate auf 9600 bps 
	}
	 
	void loop() { 
		Serial.println(analogRead(0)); // sendet den Analogwert 
		delay(1000); // pausiert fuer 1 Sekunde 
	}

# Die Befehle der serielle Schnittstelle

## Die serielle Schnittstelle prüfen

### `if (Serial)`

	void setup() { 
	  Serial.begin(9600); 
	  while (!Serial) {
	    ; // wait for serial port to connect. Needed for native USB
	  }
	} 

### `Serial.available()`

	void loop() {
	
	        // send data only when you receive data:
	        if (Serial.available() > 0) {
	                // read the incoming byte:
	                incomingByte = Serial.read();
	
	                // say what you got:
	                Serial.print("I received: ");
	                Serial.println(incomingByte, DEC);
	        }
	}
	
	availableForWrite()

## Auf die serielle Schnittstelle schreiben
### `Serial.begin()`
Setzt die Datenrate für die Datenübertragung in 'bits per second' (baud). Mit den folgenden Datenraten kann mit einem Computer kommuniziert werden: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200. 

	void setup() {
	    Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
	}
	
	void loop() {}

### `Serial.end()`
Disables serial communication, allowing the RX and TX pins to be used for general input and output. To re-enable serial communication, call Serial.begin().

### `Serial.write()`
Schreibt binäre Daten byteweise oder auch in einer Reihe von Bytes.
 to send the characters representing the digits of a number use the print() function instead.

	void setup(){
	  Serial.begin(9600);
	}
	
	void loop(){
	  Serial.write(45); // send a byte with the value 45
	
	   int bytesSent = Serial.write(“hello”); //send the string “hello” and return the length of the string.
	}
	serialEvent()

## Lesen von der seriellen Schnittstelle

### `serialEvent()`
Die Methode wird aufgerufen, sobald serielle Daten empfangen werden. Die Daten können mit `Serial.read()` gelesen werden.

	void serialEvent(){
		//statements
	}

Methoden zum Lesen von Daten aus der seriellen Schnittstelle sind u.a. `Serial.read()`, oder auch `Serial.readString()`, mit `Serial.parseFloat()` oder `Serial.parseInt()` können Zahlenwerte ausgefiltert werden.

