# F Atom und Platformio IDE Arduino unter Mac Os und Windows
**Anleitung zur Installation von Platformio IDE**
	http://docs.platformio.org/en/stable/ide/atom.html

## Schritt für Schritt
1. Atom installieren
2. Platformio-ide Package installieren
3. Install Python 2.7 (Download MSI and install)  
	- install for all users  
	- C:Python27  
	- add python.exe to PATH  
	Dann installiert sich die platformio IDE ...
4. `pip install platformio` (im Windows command)
5. install clang (clan-64bit.exe) (`http://releases.llvm.org/download.html `)  
	- C:Program FilesLLVM  
	- add to PATH for all users

**PATH**
C:Python27;C:Python27Scripts;C:Program Files (x86)ParallelsParallels ToolsApplications;C:WINDOWSsystem32;C:WINDOWS;C:WINDOWSSystem32Wbem;C:WINDOWSSystem32WindowsPowerShellv1.0;C:Usersmichaelreichart.dnxbin;C:Program FilesMicrosoft DNXDnvm;C:Program Files (x86)MitovVisuino;C:UsersmichaelreichartAppDataLocalatombin;%USERPROFILE%AppDataLocalMicrosoftWindowsApps;

**Projekt anlegen**

2. Uno einstellen

**Beim Build und Upload eines Sketches** installiert sich die air Toolchain. `installing toolchain-atmelavr @ ~1.40902.0  in Atom ...`

## Uncrustify

un-c-rustify ist der Codebeautifyer für `C/C++`. Er muss für Atom noch installiert werden.

### Installation auf Mac OS

1. Öffne das Terminal. (Dazu muss das CLI von Xcode installiert sein.)
2. Führe im Terminal aus:  
	`ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null`  
	und warte, bis der Befehl fertig gearbeitet hat.
3. Dann können Sie mit `brew install uncrustify` installieren. Fertig! Du kannst nun `uncrustify` verwendet.

### Uncrustify auf Windows installieren

1. uncrustify-0.64-win64.zip laden. `[https://sourceforge.net/projects/uncrustify/files/uncrustify/uncrustify-0.64/]`
2. Das Program unter `c:/unrustify` ausgepackten.   
	Das Verzeichnis braucht ggf. Administationsrechte, es geht auch jedem anderen Verzeichnis.

#### Das Verzeichnis zur PATH System Environment Variable hinzufügen

1. Über die Systemsteuerung `system environment variables` aufrufen.
2. Im Erweitert-Tab, den `Environment Variables` Button klicken.
3. In der `System variables` Sektion die `Path` Variable auswählen und `bearbeiten`wählen.
4. Über die `New` Schaltfläche `C:\Uncrustify` oder eigene Verzeichnis eintragen, in dem `cunrustify` installiert ist.
5. Mit `OK` sichern und schließen.
6. Über eine  `CMD` Fenster kann mit `where uncrustify` der Pfad zur uncrustify zurückgegeben werden. Bei mit wird also `C:\Uncrustify\uncrustify.exe` angezeigt.
7. Um die beautify-Einstellungen an eigene Wünsche anzupassen, muss im `arduino` Verzeichnis eine Datei zur Konfiguration angelegt `uncrustify.cfg` angelegt werden. Die Datei kann hier heruntergeladen werden: [http://uncrustify.sourceforge.net/default.cfg](http://uncrustify.sourceforge.net/default.cfg).

## Die Atom Keymap ergänzen

`crtl-alt-b` werden von den packages atom-beautify (beautifying) und PlatformIo (run code) verwendet. Für atom-beautify soll das erhalten bleiben, deshalb schalten wir key mapping für PlatformIo aus und weisen der in `keycaps.cson`  (`File -> Keymap...`)die folgenden Einträge zu:

**Unter Mac OS X**

	'atom-text-editor':
	  'ctrl-alt':'editor:""'
	  'shift-cmd-r': 'platformio-ide:target:build'
	  'ctrl-alt-b':	'atom-beautify:beautify-editor'

**Unter Windows**

	'atom-text-editor':
	  'ctrl-alt':'editor:""'
	  'shift-cmd-r': 'platformio-ide:target:build'
	  'ctrl-i':	'atom-beautify:beautify-editor'
	
