#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T14:10:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaskingAndMovingToFolders
TEMPLATE = app
DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc
UI_DIR = ./ui


SOURCES += main.cpp\
        mainwindow.cpp \
    sourceandtargetdialog.cpp \
    setsourceandtargetdialog.cpp

HEADERS  += mainwindow.h \
    sourceandtargetdialog.h \
    setsourceandtargetdialog.h

FORMS    += mainwindow.ui \
    sourceandtargetdialog.ui \
    setsourceandtargetdialog.ui
