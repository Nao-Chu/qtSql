#-------------------------------------------------
#
# Project created by QtCreator 2021-08-11T02:14:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = queryModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mysqlquerymodel.cpp

HEADERS  += mainwindow.h \
    connection.h \
    mysqlquerymodel.h

FORMS    += mainwindow.ui
