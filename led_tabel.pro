#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T18:50:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = led_tabel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    FastLED/fastled.cpp \
    FastLED/power_mgt.cpp \
    timer.cpp \
    FastLED/hsv2rgb.cpp \
    matrixlib.cpp \
    Effects/effectslist.cpp \
    showmatrix.cpp \
    FastLED/noise.cpp

HEADERS += \
        mainwindow.h \
    animation02.h \
    FastLED/fastled.h \
    FastLED/controller.h \
    FastLED/pixeltypes.h \
    FastLED/color.h \
    FastLED/lib8tion.h \
    FastLED/lib8tion/math8.h \
    FastLED/lib8tion/scale8.h \
    FastLED/lib8tion/random8.h \
    FastLED/lib8tion/trig8.h \
    FastLED/fastled_config.h \
    FastLED/power_mgt.h \
    timer.h \
    FastLED/hsv2rgb.h \
    Effects/effect.h \
    Effects/effectslist.h \
    matrixlib.h \
    Effects/erroreffect.h \
    showmatrix.h \
    Effects/testmode.h \
    Effects/01_simple_rainbow.h \
    Effects/00_slow_random.h \
    Effects/03_rain.h \
    Effects/04_all_random.h \
    Effects/05_show.h \
    Effects/06_fire.h \
    Effects/07_the_matrix.h \
    Effects/08_simple_balls.h \
    Effects/09_confetti.h \
    Effects/10_starfall.h \
    Effects/11_dynamic_square.h \
    FastLED/noise.h

FORMS += \
        mainwindow.ui
