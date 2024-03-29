QT -= gui
QT += core network sql concurrent

TEMPLATE = lib
DEFINES += LIBRARYFSM_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionfactory.cpp \
    bddrequest.cpp \
    libraryfsm.cpp

HEADERS += \
    actionfactory.h \
    actions.h \
    bddrequest.h \
    libraryFsm_global.h \
    libraryfsm.h \
    tactions.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
