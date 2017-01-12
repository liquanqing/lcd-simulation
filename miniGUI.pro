#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T11:52:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miniGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bitmapbasiclcd.cpp \
    hostplatformsurface.cpp \
    surfacewidget.cpp \
    workthread.cpp

HEADERS  += mainwindow.h \
    platformsurface.h \
    bitmapbasiclcd.h \
    hostplatformsurface.h \
    surfacewidget.h \
    workthread.h
