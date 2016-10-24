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
    layers/pcb_layers.cpp \
    geometry/geometry.cpp \
    viewers/andromeda_scene.cpp \
    viewers/andromeda_view.cpp \
    viewers/symbol_editor_view.cpp \
    shapes/drawable.cpp \
    shapes/ellipse.cpp \
    shapes/polyline.cpp \
    shapes/rect.cpp \
    grid/grid.cpp \
    layers/layer_defines.cpp

HEADERS  += mainwindow.h \
    layers/pcb_layers.h \
    geometry/geometry.h \
    tools/drawing_tool_base.h \
    viewers/andromeda_scene.h \
    viewers/andromeda_view.h \
    viewers/symbol_editor_view.h \
    shapes/shape_defines.h \
    shapes/drawable.h \
    shapes/ellipse.h \
    shapes/polyline.h \
    shapes/rect.h \
    grid/grid.h \
    layers/layer_defines.h

FORMS    += mainwindow.ui

RESOURCES += \
    fonts.qrc

DISTFILES += \
    grid/grid.pri \
    tools/tools.pri \
    layers/layers.pri \
    grid/grid.pri \
    shapes/shapes.pri
