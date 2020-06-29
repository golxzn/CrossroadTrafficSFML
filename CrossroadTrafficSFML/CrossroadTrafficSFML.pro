QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Change this paths to set your local SFML lib
INCLUDEPATH += D:\LIBRARIES\SFML-2.5.1(MinGW-7.3.0)\include
DEPENDPATH  += D:\LIBRARIES\SFML-2.5.1(MinGW-7.3.0)\include

LIBS += -LD:\LIBRARIES\SFML-2.5.1(MinGW-7.3.0)\lib\

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-system-d -lsfml-network-d -lsfml-main-d -lsfml-window-d -lsfml-graphics-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-system -lsfml-network -lsfml-main -lsfml-window -lsfml-graphics

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
    Cars.cpp \
    ElectroEngineCar.cpp \
    Game.cpp \
    GameComponents.cpp \
    GasEngineCar.cpp \
    HybridEngineCar.cpp \
    ICar.cpp \
    Rectangle.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Cars.h \
    ElectroEngineCar.h \
    Game.h \
    GameComponents.h \
    GameConstants.h \
    GasEngineCar.h \
    HybridEngineCar.h \
    ICar.h \
    Rectangle.h
