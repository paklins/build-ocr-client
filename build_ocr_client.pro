#-------------------------------------------------
#
# Project created by QtCreator 2019-07-03T14:29:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = build_ocr_client
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

CONFIG += c++11

SOURCES += \
        core/recompiler.cpp \
        forms/framelesswindow.cpp \
        styles/DarkStyle.cpp \
        forms/windowdragger.cpp \
        forms/settingswindow.cpp \
        forms/splashscreen.cpp \
        main.cpp \
        mainwindow.cpp \
        styles/onecstyle.cpp

HEADERS += \
        core/recompiler.h \
        forms/framelesswindow.h \
        styles/DarkStyle.h \
        forms/windowdragger.h \
        forms/settingswindow.h \
        forms/splashscreen.h \
        mainwindow.h \
        styles/onecstyle.h

FORMS += \
        forms/framelesswindow.ui \
        forms/settingswindow.ui \
        forms/splashscreen.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources/fonts.qrc \
    window.qrc

RC_ICONS = resources/icon.ico
