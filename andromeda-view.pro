#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:50:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = andromeda-view
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    andromeda_scene.cpp \
    andromeda_view.cpp

HEADERS  += mainwindow.h \
    andromeda_scene.h \
    andromeda_view.h

FORMS    += mainwindow.ui
