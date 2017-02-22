#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T00:28:25
#
#-------------------------------------------------

QT       += core gui\
            opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPainter
TEMPLATE = app

LIBS += -lGLU
SOURCES += ./src/main.cpp\
        ./src/mainwindow.cpp \
    src/line.cpp \
    src/circle.cpp \
    src/shape.cpp \
    src/rect.cpp \
    src/paintwidget.cpp \
    src/ellipse.cpp \
    src/drawMethods.cpp \
    src/polygon.cpp \
    src/bspline.cpp \
    src/bezierline.cpp \
    src/fill.cpp \
    src/transform.cpp \
    src/scale.cpp \
    src/rotation.cpp \
    src/lineclip.cpp \
    src/polygonclip.cpp \
    src/widget.cpp

INCLUDEPATH += ./include
HEADERS  += ./include/mainwindow.h \
    include/shape.h \
    include/circle.h \
    include/line.h \
    include/rect.h \
    include/paintwidget.h \
    include/ellipse.h \
    include/drawMethods.h \
    include/polygon.h \
    include/bspline.h \
    include/bezierline.h \
    include/fill.h \
    include/transform.h \
    include/scale.h \
    include/rotation.h \
    include/lineclip.h \
    include/polygonclip.h \
    include/widget.h
FORMS    += mainwindow.ui

#RESOURCES += \
#    resource.qrc
