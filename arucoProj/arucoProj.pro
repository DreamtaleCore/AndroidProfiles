QT += core
QT -= gui

CONFIG += c++11

TARGET = arucoProj
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += /home/yf/ws/src/uav_vision/src/detectDoll.cxx \
        /home/yf/ws/src/uav_onboard_sdk/dji_sdk_demo/src/client.cxx \
        /home/yf/ws/Projs/arucoProj/ArduinoEditDigital.cpp \
        /home/yf/ws/src/uav_guidance_sdk/src/GuidanceNode.cpp
    #camera_calibration.cpp

#HEADERS += /home/nbzd/bin/aruco-2.0.9/src/*.h
HEADERS += /home/yf/ws/src/uav_core_logic/src/generalHeader.h \
           /home/yf/ws/src/uav_core_logic/src/recvInfo.h

INCLUDEPATH += /opt/ros/indigo/include \
                /usr/local/include \
                /usr/local/include/eigen3 \
                /home/yf/bin/arduino-1.6.10/hardware/arduino/avr/cores/arduino \
                /home/yf/ws/src/uav_onboard_sdk/dji_sdk/include  \
                /home/yf/bin/arduino-1.6.10/libraries/Servo/src \
                /home/yf/bin/arduino-1.6.10/libraries/PWM \
                /home/yf/ws/src/uav_guidance_sdk/include \
                /home/yf/ws/src/uav_onboard_sdk/dji_sdk_lib/include



LIBS += /usr/local/lib/*.so \
        /opt/ros/indigo/lib/*.so

