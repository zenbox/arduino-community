# Github Desktop Client einrichten und verwenden

Für Mac Os X und Window gibt es unter [https://desktop.github.com/](https://desktop.github.com/) einen kostenlosen Github Client. Damit können sehr einfach Projekte zwischen der Arduino Community oder andere Github Projekten mit den Dateien auf dem eigenen Rechner synchronisiert werden.
Alternativ kann `git` auch als Service über das Terminal bedient werden.

Ist der Github Desktop Client installiert, kann mit den folgenden Schritten eine lokale Kopie der Arduino Community angelegt werden. Diese Kopie  kann anschließend bei Änderungen und Ergänzungen, die man gemacht hat, über den Github Desktop Client synchronisiert werden.

## Einen Git Account anlegen
Unter http://github.com müssen Sie sich einen GitHub account anlegen. Dazu hinterlegen Sie eine Email Adresse  und einen Usernamen. Der Standard Git Account ist kostenfrei.

## Einladung anfordern
Ich muss Sie als `Collaborator` zur Arduino Community einladen. Das Repository ist nicht öffentlich zugänglich. 
1. Schicken Sie mir dazu eine Email mit Ihrem Github Benutzernamen an `michael@zenbox.de`. (Das ist meine Github Emailadresse.) 
2. Ich schicke Ihnen dann eine Einladung an die Emailadresse, die Sie bei Github angegeben haben.
3. Bestätigen Sie den Link in der Email.
4. Fertig. Sie sollten jetzt über `http://github.com/zenbox` auf das Repository Zugriff haben, wenn Sie bei Github mit Ihrem Benutzer eingeloggt sind.

## Kopie (Clone) des arduino-community Projektes auf dem eigenen Rechner anlegen
Am einfachsten ist es, zur weiteren Bearbeitung das Repository auf den eigenen Rechner zu kopieren und bei Änderungen über den Github Desktop Client zu synchronisieren.

1. Im geöffneten Github Desktop Client Fenster befindet sich oben links ein Plus-Button. Er öffnet ein Menü, indem der Befehl `clone` ausgewählt wird.
2. Daraufhin öffnet sich die Liste der eigenen Repositories auf Git. hier sollte das arduino-community Repository aufgelistet werden.
3. Wählen Sie das Repository aus und weisen Sie ihm ein lokales Arbeitsverzeichnis zu.
4. Das Verzeichnis und seine Inhalte lassen sich wie gewohnt lokal bearbeiten.
5. Nach der Bearbeitung werden die Änderungen über den Github Desktop Client wieder mit dem Online Repository synchronisiert. Die Änderungen werden dort aufgeigt.

**ACHTUNG! Synchronisieren Sie das Repository über den `Sync` Button oben rechts in der Software, um Änderungen von anderen zunächst auf den eigenen Rechner zu kopieren. ** 