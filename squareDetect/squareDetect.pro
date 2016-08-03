QT += core
QT -= gui

CONFIG += c++11

TARGET = squareDetect
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/*.cpp
HEADERS += include/*.h

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/*.so
