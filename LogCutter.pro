#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T22:57:32
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogCutter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analyer/analyer.cpp \
    analyer/msganalyser.cpp \
    analyer/mloganalyser.cpp \
    analyer/m3762analyser.cpp \
    ui/analysemsgsheet.cpp

HEADERS  += mainwindow.h \
    analyer/analyer.h \
    all.h \
    analyer/msganalyser.h \
    analyer/mloganalyser.h \
    analyer/m3762analyser.h \
    ui/analysemsgsheet.h

FORMS    += mainwindow.ui
