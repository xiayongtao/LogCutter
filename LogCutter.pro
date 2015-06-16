#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T22:57:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogCutter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analyer/analyer.cpp \
    analyer/msganalyser.cpp

HEADERS  += mainwindow.h \
    analyer/analyer.h \
    all.h \
    analyer/msganalyser.h \
    analyer/analyserall.h

FORMS    += mainwindow.ui
