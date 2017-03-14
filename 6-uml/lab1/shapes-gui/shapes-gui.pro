#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T14:11:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shapes-gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp\
        "Shapes\Ellipse.cpp"\
        "Shapes\Circle.cpp"\
        "Shapes\ShapeWithFilling.cpp"\
        "Shapes\Shape.cpp"\
        "Shapes\Ray.cpp"\
        "Shapes\Line.cpp"\
        "Shapes\LineSegment.cpp"\
        "Shapes\PolygonalChain.cpp"\

HEADERS  += mainwindow.h\
            "Shapes\Ellipse.h"\
            "Shapes\Circle.h"\
            "Shapes\ShapeWithFilling.h"\
            "Shapes\Shape.h"\
            "Shapes\Ray.h"\
            "Shapes\Line.h"\
            "Shapes\LineSegment.h"\
            "Shapes\PolygonalChain.h"\

FORMS    += mainwindow.ui
