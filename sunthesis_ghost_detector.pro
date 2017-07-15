TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lphidget22

SOURCES += main.cpp \
    src/phidget/PhidgetDigitalOutput.cpp \
    src/phidget/PhidgetVoltageInput.cpp

HEADERS += \
    src/phidget/PhidgetDigitalOutput.h \
    src/phidget/PhidgetVoltageInput.h \
    src/phidget/PhidgetGenericHandlers.h
