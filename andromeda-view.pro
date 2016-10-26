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
    layers/layer_defines.cpp \
    tools/tool_base.cpp \
    logging/debug_handler.cpp \
    geometry/bounding_box.cpp \
    tools/ellipse_drawing_tool.cpp \
    tools/rect_drawing_tool.cpp \
    tools/polyline_drawing_tool.cpp \
    tools/polyline_tool_base.cpp

HEADERS  += mainwindow.h \
    layers/pcb_layers.h \
    geometry/geometry.h \
    viewers/andromeda_scene.h \
    viewers/andromeda_view.h \
    viewers/symbol_editor_view.h \
    shapes/shape_defines.h \
    shapes/drawable.h \
    shapes/ellipse.h \
    shapes/polyline.h \
    shapes/rect.h \
    grid/grid.h \
    layers/layer_defines.h \
    tools/tool_defines.h \
    tools/tool_base.h \
    logging/debug_handler.h \
    geometry/bounding_box.h \
    tools/ellipse_drawing_tool.h \
    tools/rect_drawing_tool.h \
    tools/polyline_drawing_tool.h \
    viewers/polyline_tool_base.h \
    tools/polyline_tool_base.h

FORMS    += mainwindow.ui

RESOURCES += \
    fonts.qrc
