#======================= Config ========================#
QT += core gui widgets
CONFIG += c++17

#======================== Cross ========================#

win32 {
    PLATFORM += "windows"
} else:linux {
    PLATFORM += "linux"
} else {
    message("[Cross] [Error] The current platform is not supported!");
    return();
}
message("[Cross] The target platform is $$PLATFORM")

#====================== Libraries ======================#

SFML_ROOT_DIR = $${PWD}/lib/$$PLATFORM/SFML

# D:\LIBRARIES\SFML-2.5.1(MinGW-7.3.0)\include

INCLUDEPATH += $${SFML_ROOT_DIR}/include
DEPENDPATH  += $${SFML_ROOT_DIR}/include

LIBS += -L${SFML_ROOT_DIR}/lib/

CONFIG(debug, debug|release) {
    LIBS += -lsfml-main-d \
            -lsfml-audio-d \
            -lsfml-window-d \
            -lsfml-system-d \
            -lsfml-graphics-d
}
CONFIG(release, debug|release) {
    LIBS += -lsfml-main \
            -lsfml-audio \
            -lsfml-system \
            -lsfml-window \
            -lsfml-graphics
}

#DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#======================= Sources =======================#

INCLUDEPATH += ${PWD}/inc

SOURCES += \
    src/ICar.cpp \
    src/ElectroEngineCar.cpp \
    src/GasEngineCar.cpp \
    src/HybridEngineCar.cpp \
    src/Cars.cpp \
    src/Game.cpp \
    src/GameComponents.cpp \
    src/Rectangle.cpp \
    main.cpp

HEADERS += \
    inc/Cars.h \
    inc/ElectroEngineCar.h \
    inc/Game.h \
    inc/GameComponents.h \
    inc/GameConstants.h \
    inc/GasEngineCar.h \
    inc/HybridEngineCar.h \
    inc/ICar.h \
    inc/Rectangle.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

