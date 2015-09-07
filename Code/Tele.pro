TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += avrcompile avrdude

INCLUDEPATH += /usr/lib/avr/include
INCLUDEPATH += /usr/lib/gcc/avr/4.3.5/include
INCLUDEPATH += /usr/lib/gcc/avr/4.3.5/include-fixed

MMCU  = atmega32
F_CPU = 16000000UL
include(avrcompile.pri)

ROOT_DIRECTORY = $$PWD
BUILD_DIRECTORY = $${ROOT_DIRECTORY}/../Build
EXEC_DIRECTORY = $${BUILD_DIRECTORY}

DESTDIR = $${EXEC_DIRECTORY}
OBJECTS_DIR = $${BUILD_DIRECTORY}
RCC_DIR = $${BUILD_DIRECTORY}
MOC_DIR = $${BUILD_DIRECTORY}

SOURCES += \
    main.c \
    util.c \
    handy.c \
    fetap.c

HEADERS += \
    util.h \
    handy.h \
    fetap.h
