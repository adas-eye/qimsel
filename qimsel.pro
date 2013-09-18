QT+=core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET=qimsel
TEMPLATE=app

SOURCES+=main.cpp\
         dialog.cpp\
         listwidget.cpp\
         thumbdir.cpp

HEADERS+=thumbdir.h\
         dialog.h\
         listwidget.h

FORMS+=dialog.ui
