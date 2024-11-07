QT       += core gui
QT += svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    shtriangulation.cpp \
    shvizualization.cpp \
    triangulation.cpp

HEADERS += \
    mainwindow.h \
    shtriangulation.h \
    shvizualization.h \
    triangulation.h

FORMS += \
    mainwindow.ui



INCLUDEPATH += lib/OpenCv/opencv/build/include
LIBS += -Llib/OpenCv/opencv/build/x64/vc15/lib -lopencv_world455d



RESOURCES += \
    res.qrc

INCLUDEPATH += lib/CDTLIB
LIBS += -Llib/CDTLIB -lCDT

