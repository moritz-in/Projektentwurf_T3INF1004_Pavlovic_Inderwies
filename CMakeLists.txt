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
        Game.cpp
        Game.h
        Player.h
        Player.cpp
        Objects.h
        Objects.cpp
        GameMode.h
        GameMode.cpp
        CatchMode.h
        CatchMode.cpp
        DodgeMode.h
        DodgeMode.cpp
        Gui.h
        Gui.cpp
        Square.h
        Square.cpp
        Circle.h
        Circle.cpp
        Camera.h
        Camera.cpp
)

target_link_libraries(Projektentwurf_T3INF1004_Pavlovic_Inderwies ${OpenCV_LIBS})

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")
