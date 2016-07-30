QT += core
QT -= gui

CONFIG += c++11

TARGET = arucoProj
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#SOURCES += /home/nbzd/bin/aruco-2.0.9/src/*.cpp \
#    aruco_tracker.cpp

SOURCES += \
    mymarker.cpp \
    client.cxx \
    ArduinoEdit.cpp
    #camera_calibration.cpp

#HEADERS += /home/nbzd/bin/aruco-2.0.9/src/*.h

INCLUDEPATH += /opt/ros/indigo/include \
                /usr/local/include \
                /usr/local/include/eigen3 \
                /home/yf/bin/arduino-1.6.10/hardware/arduino/avr/cores/arduino \
                /home/yf/ws/src/Onboard-SDK-ROS-3.1/dji_sdk/include    \
                /home/yf/bin/arduino-1.6.10/libraries/Servo/src


LIBS += /usr/local/lib/*.so \
        /opt/ros/indigo/lib/*.so

