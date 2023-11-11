TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        pushdownautomatasamples.cpp

HEADERS += \
    automatainstance.h \
    pushdownautomatasamples.h \
    transition.h
