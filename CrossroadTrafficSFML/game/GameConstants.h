#pragma once

#include "ICar.h"

namespace GameConstants {
    constexpr int   centreStrip{ 5 };
    constexpr int   initialCarsCount{ 5 };
    constexpr int   defaultFuel{ 5000 };
    constexpr float defaultSpeed{ 1 };
    constexpr float defaultRange{ 10 };
    constexpr float defaultSpeedChain{ 0.1f };

    constexpr auto defaultCarWidth{ 50u };
    constexpr auto defaultCarHeight{ 90u };
    const auto defaultCarRectangle{
        Rectangle{defaultCarWidth, defaultCarHeight}
    };
    const auto defaultCarFuturePositionColor{ sf::Color{ 50, 40, 100, 150 } };

    constexpr auto defaultDirection{ ICar::eDirection::DOWN };
    namespace ScreenInfo {
        constexpr uint WIDTH = 1024u;
        constexpr uint HEIGHT = 712u;
        constexpr char TITLE[] = "Crossroad traffic";
        const sf::Vector2u SIZE{ WIDTH, HEIGHT };
    }
    constexpr char defaultBackgroundImgPath[] = "res/img/background_1.jpg";
    constexpr char defaultUIFontPath[] = "res/fonts/UI_font.ttf";
}
