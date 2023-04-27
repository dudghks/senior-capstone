QT       += core gui
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    equationsubblock.cpp \
    blocktextedit.cpp \
    main.cpp \
    mainwindow.cpp \
    ribbon.cpp \
    ribbonbuttongroup.cpp \
    ribbonsmallbuttonsgroup.cpp \
    ribbontabcontent.cpp

HEADERS += \
    blocktextedit.h \
    equationsubblock.h \
    mainwindow.h \
    ribbon.h \
    ribbonbuttongroup.h \
    ribbonsmallbuttonsgroup.h \
    ribbontabcontent.h

FORMS += \
    mainwindow.ui \
    ribbonbuttongroup.ui \
    ribbonsmallbuttonsgroup.ui \
    ribbontabcontent.ui

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

