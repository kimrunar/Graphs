TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    ffa.h \
    ../../graphs/edge.h \
    ../../graphs/graph.h \
    ../../graphs/graphadt.h \
    ../../graphs/node.h
