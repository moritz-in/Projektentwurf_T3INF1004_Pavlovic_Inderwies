cmake_minimum_required(VERSION 3.11)
project(Projektentwurf_T3INF1004_Pavlovic_Inderwies)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
set(OpenCV_DIR "/opt/homebrew/opt/opencv/lib/cmake/opencv4")  # oder /usr/local/... für Intel
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Projektentwurf_T3INF1004_Pavlovic_Inderwies
        main.cpp
        src/Game.cpp
        include/Game.h
        include/Player.h
        src/Player.cpp
        include/Objects.h
        include/GameMode.h
        src/GameMode.cpp
        include/CatchMode.h
        src/CatchMode.cpp
        include/DodgeMode.h
        src/DodgeMode.cpp
        include/Gui.h
        src/Gui.cpp
        include/Square.h
        src/Square.cpp
        include/Circle.h
        src/Circle.cpp
        include/Camera.h
        src/Camera.cpp
)

target_link_libraries(Projektentwurf_T3INF1004_Pavlovic_Inderwies ${OpenCV_LIBS})

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")
