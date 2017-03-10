#-------------------------------------------------
#
# Project created by QtCreator 2017-03-03T09:08:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CorGestBase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogconnect.cpp

HEADERS  += mainwindow.h \
    dialogconnect.h

FORMS    += mainwindow.ui \
    dialogconnect.ui
TRANSLATIONS += CorGestBase_fr_FR.ts \
                CorGestBase_en.ts
