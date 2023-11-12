TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        automataexecution.cpp \
        main.cpp \
        pushdownautomatasamples.cpp

HEADERS += \
    automataexecution.h \
    automatainstance.h \
    pushdownautomatasamples.h \
    transition.h \
    transitionpossibility.h
