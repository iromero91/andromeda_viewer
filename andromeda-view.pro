#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:50:40
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

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
    symbol_editor_view.cpp \
    geometry.cpp \
    andromeda_ellipse.cpp \
    layer_definitions.cpp \
    pcb_layers.cpp \
    andromeda_rect.cpp

HEADERS  += mainwindow.h \
    andromeda_scene.h \
    andromeda_view.h \
    andromeda_grid.h \
    andromeda_drawable.h \
    lwpolyline.h \
    symbol_editor_view.h \
    geometry.h \
    andromeda_ellipse.h \
    layer_definitions.h \
    drawable_enums.h \
    pcb_layers.h \
    andromeda_rect.h

FORMS    += mainwindow.ui

RESOURCES += \
    fonts.qrc
