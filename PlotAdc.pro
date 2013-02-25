# Qt project file - qmake uses his to generate a Makefile

QT       += core gui

CONFIG += debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlotAdc

LIBS += -lqwt -lm -lbcm2835 -lrt

HEADERS += window.h adc.h gz_clk.h

SOURCES += main.cpp window.cpp adc.cpp gz_clk.c
