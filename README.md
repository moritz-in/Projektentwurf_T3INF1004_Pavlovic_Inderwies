# Programmentwurf

## Beschreibung
Dieses Projekt ist ein interaktives Spiel mit gesichtserkennung, welches mit OpenCV in der Sprache C++ implementiert wurde. Das Spiel nutzt die Webcam des Ausführenen Gerätes, um das Gesicht des Spielers zu erkennen und als "Steuerelement" zu verwenden.

Folgende Spielmodi stehen zur Verfügung:

1. DodgeMode:
    - Der Spieler muss Objekten, welche vom Bildschirm herunterfallen ausweichen
    - Trifft ein ball das Gesicht wird das Spiel beendet.
    - für jeden Ball der den Boden erreicht bekommt der Spieler einen Punkt
2. CatchMode:
    - Der Spieler muss grüne Objekte fangen und dabei roten Objekten ausweichen
    - Das fangen der grünen Objekte gibt dabei einen Punkt, der roten einen Minuspunkt
    - Der Punktestand kann dabei nicht geringer als null werden
    - Das Spiel endet, wenn die anzahl der zuvor ausgewählten Objekte vom Bildschirm gefallen sind

Das Projekt besteht aus verschiedenen Hauptkomponenten:
- Kamerastuerung: Erfassung und Verarbeitung der Videoframes
- Gesichtserkennung: Verwendung der Haar-Cascades zur Gesichtserkennung
- GUI: Zeichnen der Spielobjekte und Anzeigen des Punktestands
- Objektverwaltung: Erstellung, Bewegung und Kollisionserkennung der Spielobjekte

## UML Diagramm




## How to run this program

- Stichpunkt:
```shell
mkdir build
echo "Place the haarcascade file in this directory."
```
- Stichpunkt:
```shell
cd build
cmake ..
cmake --build . --target Projektentwurf_T3INF1004_Pavlovic_Inderwies
./Projektentwurf_T3INF1004_Pavlovic_Inderwies
```
## Bedienung
1. Bei Programmstart Namen eingeben
2. Spielmodus wählen (1. = Ausweichen, 2 = Einfangen)
3. Im CatchMode die gewünschte Objektanzahl eingeben
4. Spiel mit der Webcam steuern:
   1. Gesicht bewegen, um Objekten auszuweichen oder sie zu fangen
   2. ESC-Taste drücken, um das Spiel sofort zu beenden
5. Bei Spielende werden der Erreichte Punktestand zum Namen angezeigt 