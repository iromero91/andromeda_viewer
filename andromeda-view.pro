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
    shapes/ellipse.cpp \
    shapes/polyline.cpp \
    grid/grid.cpp \
    layers/layer_defines.cpp \
    tools/tool_base.cpp \
    logging/debug_handler.cpp \
    geometry/bounding_box.cpp \
    tools/ellipse_drawing_tool.cpp \
    tools/rect_drawing_tool.cpp \
    tools/polyline_drawing_tool.cpp \
    tools/polyline_tool_base.cpp \
    base/andromeda_object.cpp \
    shapes/drawable_base.cpp \
    shapes/drawable_primitive.cpp \
    tools/polyline_editing_tool.cpp

HEADERS  += mainwindow.h \
    layers/pcb_layers.h \
    geometry/geometry.h \
    viewers/andromeda_scene.h \
    viewers/andromeda_view.h \
    viewers/symbol_editor_view.h \
    shapes/shape_defines.h \
    shapes/ellipse.h \
    shapes/polyline.h \
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
    tools/polyline_tool_base.h \
    base/andromeda_object.h \
    shapes/drawable_base.h \
    shapes/drawable_primitive.h \
    tools/polyline_editing_tool.h

FORMS    += mainwindow.ui

RESOURCES += \
    fonts.qrc
