QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additem.cpp \
    addmember.cpp \
    adminwindow.cpp \
    changemember.cpp \
    dbmanager.cpp \
    deleteitem.cpp \
    deletemember.cpp \
    edititem.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    managerwindow.cpp

HEADERS += \
    additem.h \
    addmember.h \
    adminwindow.h \
    changemember.h \
    dbmanager.h \
    deleteitem.h \
    deletemember.h \
    edititem.h \
    loginwindow.h \
    mainwindow.h \
    managerwindow.h

FORMS += \
    additem.ui \
    addmember.ui \
    adminwindow.ui \
    changemember.ui \
    deleteitem.ui \
    deletemember.ui \
    edititem.ui \
    loginwindow.ui \
    mainwindow.ui \
    managerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
