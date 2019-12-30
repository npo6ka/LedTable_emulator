cmake_minimum_required(VERSION 3.1.0)

project(LEDTableEmulator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DQT_DEPRECATED_WARNINGS)

find_package(Qt5Widgets)
find_package(Qt5Network)

add_executable(LEDTableEmulator
    mainwindow.ui
    main.cpp
    mainwindow.cpp
    FastLED/fastled.cpp
    FastLED/power_mgt.cpp
    timer.cpp
    FastLED/hsv2rgb.cpp
    matrixlib.cpp
    Effects/effectslist.cpp
    showmatrix.cpp
    FastLED/noise.cpp)

target_include_directories(LEDTableEmulator PRIVATE FastLED)
target_link_libraries(LEDTableEmulator Qt5::Widgets)
target_link_libraries(LEDTableEmulator Qt5::Network)
