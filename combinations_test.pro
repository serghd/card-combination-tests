QT       += core gui

QMAKE_CXXFLAGS += -std=c++14 -g -W -Wall -Wextra -Wno-deprecated-declarations -Wno-format-truncation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = combinations_test
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

OBJECTS_DIR = ./tmp
MOC_DIR = ./tmp
RCC_DIR = ./tmp
DESTDIR = ./
UI_DIR = ./ui

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    CardsConteiner.cpp \
    Deck.cpp \
    Holdem.cpp \
    Omaha.cpp

HEADERS += \
    mainwindow.h \
    CardsConteiner.h \
    common.h \
    Deck.h \
    Holdem.h \
    Omaha.h

FORMS += \
    ui/mainwindow.ui

RESOURCES += \
    rc.qrc
