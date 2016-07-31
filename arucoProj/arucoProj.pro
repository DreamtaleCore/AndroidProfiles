QT += core
QT -= gui

CONFIG += c++11

TARGET = arucoProj
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += /home/yf/ws/src/uav_vision/src/detectDoll.cxx
    #camera_calibration.cpp

#HEADERS += /home/nbzd/bin/aruco-2.0.9/src/*.h
HEADERS += /home/yf/ws/src/uav_core_logic/src/generalHeader.h \
           /home/yf/ws/src/uav_core_logic/src/recvInfo.h

INCLUDEPATH += /opt/ros/indigo/include \
                /usr/local/include \
                /usr/local/include/eigen3 \
                /home/yf/bin/arduino-1.6.10/hardware/arduino/avr/cores/arduino \
                /home/yf/ws/src/onboard_sdk/dji_sdk/include    \
                /home/yf/bin/arduino-1.6.10/libraries/Servo/src


LIBS += /usr/local/lib/*.so \
        /opt/ros/indigo/lib/*.so

