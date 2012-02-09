#-------------------------------------------------
#
# Project created by QtCreator 2011-10-31T19:43:16
#
#-------------------------------------------------

QT       += core gui network

TARGET = ftp_client
TEMPLATE = app
TRANSLATIONS += ftpclient_zh.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    picwidget.cpp \
    mainwindow.cpp \
    main.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    qt4.h \
    settingsdialog.h \
    resource.h \
    qt4.h \
    picwidget.h \
    mainwindow.h \
    connectdialog.h

FORMS    += \
    mainwindow.ui \
    SettingsDialog.ui \
    connectDialog.ui

RESOURCES += \
    res.qrc
OTHER_FILES+= \ rec.rc

RC_FILE = \
  rec.rc



