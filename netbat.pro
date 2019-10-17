#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T12:06:27
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = netbat
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    connection.cpp \
    dialog.cpp \
    login_dialog.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    connection.h \
    dialog.h \
    login_dialog.h \
    logindialog_ui.h \
    sql_connnect.h \
    qcustomplot.h

FORMS    += widget.ui
