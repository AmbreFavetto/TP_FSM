QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testsearchfiles.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libraryFsm/release/ -llibraryFsm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libraryFsm/debug/ -llibraryFsm
else:unix: LIBS += -L$$OUT_PWD/../libraryFsm/ -llibraryFsm

INCLUDEPATH += $$PWD/../libraryFsm
DEPENDPATH += $$PWD/../libraryFsm
