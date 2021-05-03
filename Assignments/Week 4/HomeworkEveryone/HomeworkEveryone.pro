#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl1
TEMPLATE = app


SOURCES += main.cpp\
    chaikin.cpp \
    interpolatingcubicsubdivision.cpp \
        mainwindow.cpp \
    mesh.cpp \
    objfileprocessing.cpp \
    oglwidget.cpp \
    readobj.cpp \
    triangle.cpp \
    vec3.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    chaikin.h \
    interpolatingcubicsubdivision.h \
    mesh.h \
    objfileprocessing.h \
    oglwidget.h \
    readobj.h \
    triangle.h \
    vec3.hpp \
    vertex.h

FORMS    += mainwindow.ui

DISTFILES += \
    Dot.obj \
    README \
    line.obj \
    tetra.obj
