# Reaktionsspiel mit Gesichtserkennung

## Beschreibung
Interaktives Spiel mit Gesichtserkennung, implementiert in C++ mit OpenCV. Nutzt die Webcam zur Steuerung durch Gesichtsbewegungen. Das Spiel besteht aus mehreren Kernklassen:

### Wichtigste Klassen
1. **Game**: Hauptsteuerungsklasse, verwaltet Spielablauf und Moduswechsel
2. **GameMode**: Abstrakte Basisklasse für Spielmodi (DodgeMode und CatchMode)
3. **Player**: Verwaltet Spielerinformationen und Punktestand
4. **Object**: Basisklasse für Spielobjekte (Kreise und Quadrate)
5. **Camera**: Kamerasteuerung und Frame-Erfassung
6. **Gui**: Zeichnet Spieloberfläche und verwaltet Anzeige

### Spielmodi
1. **DodgeMode (Ausweichmodus)**:
   - Ausweichen fallender Objekte
   - Kollision beendet Spiel
   +1 Punkt pro Objekt am Boden

2. **CatchMode (Fangmodus)**:
   - Grüne Quadrate fangen (+1 Punkt)
   - Rote Kreise vermeiden (-1 Punkt)
   - Punktestand ≥ 0
   - Ende bei allen Objekten gespawnt und verschwunden

## UML Diagramm
![UML Diagramm](https://github.com/user-attachments/assets/0b524262-b1a6-407b-877c-ff09650579b5)

## Installation

### Windows
**Voraussetzungen:**
- CMake ≥ 3.15
- OpenCV ≥ 4.5

**Installation:**
```shell

# 1. Repository klonen
git clone https://github.com/moritz-in/Projektentwurf_T3INF1004_Pavlovic_Inderwies.git
cd Projektentwurf_T3INF1004_Pavlovic_Inderwies

# 2. Build-Verzeichnis erstellen
mkdir build
cd build

# 3. CMake konfigurieren
cmake .. -A x64

# 4. Kompilieren
cmake --build . --config Release

# 5. Haar-Cascade kopieren
copy "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" .

# 6. Programm starten
.\Release\Projektentwurf_T3INF1004_Pavlovic_Inderwies.exe
```

### macOS
**Voraussetzungen:**
- CMake ≥ 3.15
- OpenCV ≥ 4.5

**Installation:**
```shell

# 1. Repository klonen
git clone https://github.com/moritz-in/Projektentwurf_T3INF1004_Pavlovic_Inderwies.git
cd Projektentwurf_T3INF1004_Pavlovic_Inderwies

# 2. Build-Verzeichnis erstellen
mkdir build
cd build

# 3. CMake konfigurieren
cmake ..

# 4. Kompilieren
make

# 5. Haar-Cascade verlinken
ln -s /usr/local/opt/opencv/share/opencv4/haarcascades/haarcascade_frontalface_default.xml .

# 6. Programm starten
./Projektentwurf_T3INF1004_Pavlovic_Inderwies
```

## Bedienung
1. Namen eingeben
2. Spielmodus wählen (1 = DodgeMode, 2 = CatchMode)
3. Im CatchMode Objektanzahl festlegen
4. Spielsteuerung:
   - Gesicht bewegen zum Ausweichen/Fangen
   - ESC zum Beenden
5. Spielende: Name und Punktestand werden angezeigt

## Fehlerbehebung

### Allgemein
| Problem | Lösung |
|---------|--------|
| **OpenCV nicht gefunden** | `cmake -DOpenCV_DIR="<pfad/zu/opencv/build>" ..` |
| **Haar-Cascade Fehler** | Absoluten Pfad angeben: `m_faceCascade.load("/vollstaendiger/pfad.xml")` |
| **Kollisionsprobleme** | `cv::Rect expandedFace = faces[0] + cv::Size(20,20) - cv::Point(10,10);` |

### Windows-spezifisch
| Problem | Lösung |
|---------|--------|
| **Kamera nicht verfügbar** | Geräteindex ändern: `Camera(1)` in Camera.h |
| **Niedrige Framerate** | Auflösung reduzieren: `Camera(0, 640, 480)` |

### macOS-spezifisch
| Problem | Lösung |
|---------|--------|
| **Kamera-Berechtigung** | Systemeinstellungen > Sicherheit > Kamera > Terminal erlauben |
| **OpenCV-Linker-Fehler** | `brew link --force opencv` |

## Tests
```shell

# Windows
.\Release\run_tests.exe --gtest_color=yes
```
```shell

# macOS
./run_tests --gtest_color=yes
```