# Reaktionsspiel mit Gesichtserkennung

## Beschreibung
Dieses Projekt ist ein interaktives Spiel mit Gesichtserkennung, das mit OpenCV in C++ implementiert wurde. Das Spiel nutzt die Webcam des Geräts, um das Gesicht des Spielers zu erkennen und als Steuerelement zu verwenden.

### Spielmodi
1. **DodgeMode (Ausweichmodus)**:
   - Der Spieler muss Objekten ausweichen, die vom oberen Bildschirmrand herunterfallen
   - Kollision mit einem Objekt beendet das Spiel
   - Für jedes Objekt, das den Boden erreicht, erhält der Spieler +1 Punkt

2. **CatchMode (Fangmodus)**:
   - Der Spieler muss grüne Quadrate fangen und roten Kreisen ausweichen
   - Grüne Quadrate: +1 Punkt
   - Rote Kreise: -1 Punkt (Punktestand kann nicht unter 0 fallen)
   - Spiel endet, wenn alle vordefinierten Objekte gespawnt sind und vom Bildschirm verschwunden sind

### Hauptkomponenten
- **Kamerasteuerung**: Erfassung und Verarbeitung von Videoframes
- **Gesichtserkennung**: Verwendung von Haar-Cascades zur Echtzeit-Gesichtserkennung
- **GUI-System**: Zeichnen von Spielobjekten und Anzeige von Spielinformationen
- **Objektverwaltung**: Dynamische Erstellung, Bewegung und Kollisionserkennung
- **Spielmodi**: Modular implementierte Spielmechaniken

## UML Diagramm
![UML Diagramm](https://github.com/user-attachments/assets/0b524262-b1a6-407b-877c-ff09650579b5)

## Installation und Ausführung

### Voraussetzungen
- Windows 10/11
- CMake (Version 3.15 oder höher)
- OpenCV (Version 4.5 oder höher)
- Visual Studio (2019 oder höher) mit C++-Workload
- Git (optional)

### Schritt-für-Schritt Anleitung

```shell
# 1. Repository klonen
git clone https://github.com/moritz-in/Projektentwurf_T3INF1004_Pavlovic_Inderwies.git
cd Projektentwurf_T3INF1004_Pavlovic_Inderwies

# 2. Build-Verzeichnis erstellen
mkdir build
cd build

# 3. CMake konfigurieren (Anpassen des OpenCV-Pfads wenn nötig)
cmake .. -G "Visual Studio 16 2019" -A x64

# 4. Projekt kompilieren
cmake --build . --config Release --target ALL_BUILD

# 5. Haar-Cascade Datei kopieren (von OpenCV Installation)
copy "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" .

# 6. Programm starten
.\Release\Projektentwurf_T3INF1004_Pavlovic_Inderwies.exe
```

### Tests ausführen
```shell
cd build
.\Release\run_tests.exe --gtest_color=yes
```

## Bedienung
1. Bei Programmstart Namen eingeben
2. Spielmodus wählen:
   - `1` für DodgeMode (Ausweichen)
   - `2` für CatchMode (Einfangen)
3. Im CatchMode die gewünschte Objektanzahl eingeben
4. Spiel mit der Webcam steuern:
   - Gesicht bewegen, um Objekten auszuweichen oder sie zu fangen
   - ESC-Taste drücken, um das Spiel zu beenden
5. Bei Spielende werden Name und Punktestand angezeigt

## Häufige Fehler und Lösungen

### Build-Fehler
| Fehler | Lösung |
|--------|--------|
| **CMake findet OpenCV nicht** | `cmake -DOpenCV_DIR="C:/pfad/zu/opencv/build" ..` |
| **Linker-Fehler bei OpenCV** | Build-Verzeichnis löschen und neu konfigurieren |

### Laufzeitfehler
| Fehler | Lösung |
|--------|--------|
| **Kamera wird nicht geöffnet** | `Camera(int deviceIndex = 0, int width = 640, int height = 480);` |
| **Haar-Cascade wird nicht geladen** | Absoluten Pfad angeben: `m_faceCascade.load("C:/vollstaendiger/pfad.xml")` |
| **Keine Gesichtserkennung** | Beleuchtung verbessern, `detectMultiScale` Parameter anpassen |
| **Niedrige Framerate** | Auflösung reduzieren: `m_cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);` |

### Spielprobleme
| Problem | Lösung |
|---------|--------|
| **Falsche Kollisionserkennung** | `cv::Rect expandedFace = faces[0] + cv::Size(20,20) - cv::Point(10,10);` |
| **Objekte zu schnell/langsam** | Geschwindigkeit anpassen: `spawnObject(3, color, shape);` |

## Tests
```shell
# Tests ausführen
cd build
.\Release\run_tests.exe --gtest_color=yes

# Erwartete Ausgabe
[==========] Running 8 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from PlayerTest
[ RUN      ] PlayerTest.InitialScoreZero
[       OK ] PlayerTest.InitialScoreZero (0 ms)
...
[  PASSED  ] 8 tests.
```

