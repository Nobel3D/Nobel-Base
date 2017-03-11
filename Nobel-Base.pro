#-------------------------------------------------
#
# Project created by QtCreator 2017-02-12T21:43:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = Nobel
TEMPLATE = lib

DEFINES += NOBELBASE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Data/Float.cpp \
    src/Data/Memory.cpp \
    src/Data/NString.cpp \
    src/Data/Time.cpp \
    src/Data/Timer.cpp \
    src/Management/Log.cpp \
    src/Management/NException.cpp \
    src/Management/Program.cpp \
    src/Management/Thread.cpp \
    src/Math/Math.cpp \
    src/Stream/Console.cpp \
    src/Stream/NFile.cpp \
    src/Stream/NStream.cpp \
    src/Stream/Filename.cpp \
    src/Data/Convert.cpp

HEADERS +=\
    src/Data/Array.h \
    src/Data/Float.h \
    src/Data/List.h \
    src/Data/Memory.h \
    src/Data/NString.h \
    src/Data/Time.h \
    src/Data/Timer.h \
    src/Data/Translate.h \
    src/Management/Log.h \
    src/Management/NException.h \
    src/Management/Program.h \
    src/Management/Thread.h \
    src/Math/Math.h \
    src/Stream/Console.h \
    src/Stream/NFile.h \
    src/Stream/NStream.h \
    src/def.h \
    src/NBL.h \
    src/Stream/Filename.h \
    src/Data/Convert.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/src
