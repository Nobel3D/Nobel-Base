TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += test/main.cpp

LIBS += -L$$PWD/bin -lNobel-Base

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/bin
