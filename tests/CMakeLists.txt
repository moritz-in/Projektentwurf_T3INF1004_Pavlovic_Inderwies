cmake_minimum_required(VERSION 3.10)
project(Reaktionsspiel_Tests)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ../include)

set(SOURCES
        Player_test.cpp
        Object_test.cpp
        CatchMode_test.cpp
        DodgeMode_test.cpp
        GameMode_test.cpp
        Gui_test.cpp
        ../src/Gui.cpp
        ../src/Player.cpp
        ../src/Circle.cpp
        ../src/Square.cpp
        ../src/GameMode.cpp
        ../src/CatchMode.cpp
        ../src/DodgeMode.cpp
)

add_executable(run_tests ${SOURCES})
target_link_libraries(run_tests gtest gtest_main pthread ${OpenCV_LIBS})

# Use FetchContent to download GoogleTest
include(FetchContent)

FetchContent_Declare(
        googletest
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)