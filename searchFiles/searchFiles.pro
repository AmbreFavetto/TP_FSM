QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionfactory.cpp \
    bddrequest.cpp \
    fsm.cpp \
    helpwindow.cpp \
    indexer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    actionfactory.h \
    actions.h \
    bddrequest.h \
    fsm.h \
    helpwindow.h \
    indexer.h \
    mainwindow.h \
    tactions.h

FORMS += \
    helpwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
