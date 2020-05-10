#-------------------------------------------------
#
# Project created by QtCreator 2020-04-26T13:17:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoALSE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    formulario_paciente.cpp \
    formulario_usuario.cpp \
    db_local.cpp \
    clave_erronea.cpp

HEADERS += \
        mainwindow.h \
    formulario_paciente.h \
    formulario_usuario.h \
    db_local.h \
    clave_erronea.h

FORMS += \
        mainwindow.ui \
    formulario_paciente.ui \
    formulario_usuario.ui \
    clave_erronea.ui

LIBS += \
        -lsqlite3
