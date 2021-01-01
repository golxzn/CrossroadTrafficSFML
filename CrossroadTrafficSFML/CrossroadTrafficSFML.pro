#======================= Config ========================#
message("[Config] Start configuring project $$TARGET")
QT += core gui widgets opengl
CONFIG += c++17
message("[Config] QT:     $$QT")
message("[Config] CONFIG: $$CONFIG")

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

#======================= Sources =======================#

INCLUDEPATH +=  \
    basics      \
    cars        \
    game        \
    handlers    \
    screen      \
    res

SOURCES +=                      \
    basics/Rectangle.cpp        \
    cars/ICar.cpp               \
    cars/ElectroEngineCar.cpp   \
    cars/GasEngineCar.cpp       \
    cars/HybridEngineCar.cpp    \
    cars/Cars.cpp               \
    game/Game.cpp               \
    handlers/eventhandler.cpp   \
    screen/scene.cpp            \
    screen/screenmgr.cpp        \
    screen/userinterface.cpp    \
    main.cpp

HEADERS +=                      \
    basics/Rectangle.h          \
    basics/singleton.h          \
    cars/ICar.h                 \
    cars/ElectroEngineCar.h     \
    cars/GasEngineCar.h         \
    cars/HybridEngineCar.h      \
    cars/Cars.h                 \
    game/Game.h                 \
    game/GameConstants.h        \
    handlers/eventhandler.h     \
    screen/scene.h              \
    screen/screenmgr.h          \
    screen/userinterface.h      \
    platform.h

message("[Sources] Pathes:")
message("  -> $$INCLUDEPATH")

message("[Sources] Sources:")
message("  -> $$SOURCES")

message("[Sources] Headers:")
message("  -> $$HEADERS")

#====================== Libraries ======================#

message("[Libraries] Start linking SFML")
SFML_ROOT_DIR = $${PWD}/lib/SFML-2.5.1-$$PLATFORM
message("[Libraries] SFML root directory: $$SFML_ROOT_DIR")

INCLUDEPATH += $$SFML_ROOT_DIR/include
DEPENDPATH  += $$SFML_ROOT_DIR/include

LIBS += -L$$SFML_ROOT_DIR/lib

if(contains(PLATFORM, "linux")) {
    SFML_LIBS_DEBUG =   \
        -lsfml-system   \
        -lsfml-window   \
        -lsfml-graphics
    SFML_LIBS_RELEASE = $$SFML_LIBS_DEBUG
} else {
    SFML_LIBS_DEBUG =   \
        -lsfml-system   \
        -lsfml-window   \
        -lsfml-graphics
    SFML_LIBS_RELEASE = \
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

message("[Libraries] Linker options: $$LIBS")

#====================== Other ======================#

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Copy dependencies in build directory
# @ToDo: Make copying files from res to OUT_PWD
# message("[Other] Copying dependencies")
# message("[Other] [Copy] $$PWD/res -> $$OUT_PWD/res")

