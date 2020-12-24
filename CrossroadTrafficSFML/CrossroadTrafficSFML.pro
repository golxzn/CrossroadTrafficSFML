#======================= Config ========================#
QT += core gui widgets opengl
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

SFML_ROOT_DIR = $${PWD}/lib/SFML-2.5.1-$$PLATFORM

INCLUDEPATH += $$SFML_ROOT_DIR/include
DEPENDPATH  += $$SFML_ROOT_DIR/include

LIBS += -L$$SFML_ROOT_DIR/lib/

if(contains(PLATFORM, "linux")) {
    SFML_LIBS_DEBUG = \
        -lsfml-audio \
        -lsfml-system \
        -lsfml-window \
        -lsfml-graphics
    SFML_LIBS_RELEASE = $$SFML_LIBS_DEBUG
} else {
    SFML_LIBS_DEBUG = \
        -lsfml-main \
        -lsfml-audio \
        -lsfml-system \
        -lsfml-window \
        -lsfml-graphics
    SFML_LIBS_RELEASE = \
        -lsfml-main-d \
        -lsfml-audio-d \
        -lsfml-window-d \
        -lsfml-system-d \
        -lsfml-graphics-d
}

CONFIG(debug, debug|release) {
    LIBS += $$SFML_LIBS_DEBUG
}
CONFIG(release, debug|release) {
    LIBS += $$SFML_LIBS_RELEASE
}

#======================= Sources =======================#

INCLUDEPATH += inc

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


