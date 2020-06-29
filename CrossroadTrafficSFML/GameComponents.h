#pragma once

#include "Cars.h"

class GameComponents {
public:
    GameComponents(int initCarsCount     = GameConstants::initialCarsCount,
                   unsigned windowWidth  = GameConstants::ScreenInfo.WIDTH,
                   unsigned windowHeight = GameConstants::ScreenInfo.HEIGHT);

    bool setBackground(const char* filePath);
    void setCars(const Cars& cars);

    sf::Texture backgroundTexture() const;
    sf::Sprite  background()        const;

    Cars mCars;

private:
    sf::Texture mBackgroundTexture;
    sf::Sprite  mBackground;

    unsigned mWindowWidth;
    unsigned mWindowHeight;
};

