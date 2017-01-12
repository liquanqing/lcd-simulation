#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T16:41:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lcd.cpp \
    mainwidget.cpp \
    drawwidget.cpp \
    menu_low_level/menu_low_level.c \
    menu_low_level/menu_msg.c

HEADERS  += mainwindow.h \
    lcd.h \
    mainwidget.h \
    drawwidget.h \
    menu_low_level/menu_low_level.h \
    menu_low_level/menu_msg.h

DISTFILES += \
    README.md
