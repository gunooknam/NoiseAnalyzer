QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dialog.cpp \
    MainPaintWidget.cpp \
    NoiseAnalyzer.cpp \
    main.cpp

HEADERS += \
    Define.h \
    Dialog.h \
    MainPaintWidget.h \
    NoiseAnalyzer.h

FORMS += \
    NoiseAnalyzer.ui \
    dialog.ui


INCLUDEPATH += C:\\opencv\\build\\include

LIBS += -LC:\\opencv\\build\\x64\\vc14\\lib
LIBS += -lopencv_core340d
LIBS += -lopencv_core340
LIBS += -lopencv_world340d
LIBS += -lopencv_world340

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
