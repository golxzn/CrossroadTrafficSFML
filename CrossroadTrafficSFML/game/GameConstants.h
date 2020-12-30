#pragma once

#include "ICar.h"

namespace GameConstants {
    const int   centreStrip{ 5 };
    const int   initialCarsCount{ 5 };
    const int   defaultFuel{ 5000 };
    const float defaultSpeed{ 1 };
    const float defaultRange{ 10 };
    const float defaultSpeedChain{ 0.1f };

    const auto defaultCarWidth{ 50u };
    const auto defaultCarHeight{ 90u };
    const auto defaultCarRectangle{
        Rectangle{defaultCarWidth, defaultCarHeight}
    };

    const auto defaultDirection{ ICar::eDirection::DOWN };
    const struct {
        const uint WIDTH;
        const uint HEIGHT;
        const char *TITLE;
    } ScreenInfo { 1024, 768, "Crossroad traffic" };
}
