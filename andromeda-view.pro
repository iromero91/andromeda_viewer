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
    andromeda_view.cpp \
    andromeda_grid.cpp \
    andromeda_drawable.cpp \
    lwpolyline.cpp \
    symbol_editor_view.cpp

HEADERS  += mainwindow.h \
    andromeda_scene.h \
    andromeda_view.h \
    andromeda_grid.h \
    andromeda_drawable.h \
    lwpolyline.h \
    symbol_editor_view.h

FORMS    += mainwindow.ui
