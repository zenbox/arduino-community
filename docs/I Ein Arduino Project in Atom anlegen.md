# I Ein Arduino Project in Atom  anlegen

1. In der `platformio` Leiste den `initalize` Button (![](figures/icon.png)) suchen und auswählen.
2. Im geöffneten Dialogfenster das Board (hier Arduino Uno) aussuchen und ein Projektverzeichnis (`c:/Documents/Arduino/my-new-project-name`) anlegen.
3. `platformio` legt eine Verzeichnisstruktur an.
4. Im Ordner `src` (source = Quelltext) eine neue Datei mit Name `main.cpp` erzeugen. Die Datei MUSS diesen Namen haben. `cpp`ist die Dateiendung für `C++` Programmdateien.
5. Zu Beginn muss in der Projektdatei die Arduino Library eingebunden werden.

	 #include <Arduino.h>
	/**
	 * @name project name
	 * @desc a short description
	 */
	...

6. Fertig, danach kann wie gewohnt programmiert werden.
