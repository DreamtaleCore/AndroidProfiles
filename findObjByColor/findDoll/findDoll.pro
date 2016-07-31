QT += core
QT -= gui

CONFIG += c++11

TARGET = findDoll
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    findsquire.cpp

HEADERS += Onject.h

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/*.so
