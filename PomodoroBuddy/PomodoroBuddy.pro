QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alertbox.cpp \
    iowrapper.cpp \
    main.cpp \
    settingsbox.cpp \
    statsbox.cpp \
    widget.cpp

HEADERS += \
    alertbox.h \
    iowrapper.h \
    settingsbox.h \
    statsbox.h \
    widget.h

FORMS += \
    alertbox.ui \
    settingsbox.ui \
    statsbox.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#Windows icon
win32 {
    RC_FILE = pomodorobuddy.rc
}
