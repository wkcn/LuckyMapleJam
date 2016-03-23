#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T20:54:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET = LuckyMapleJam
TEMPLATE = app
CONFIG += static



SOURCES += main.cpp\
        mainwindow.cpp \
    Defines.cpp

HEADERS  += mainwindow.h \
    Defines.h

FORMS    += mainwindow.ui
