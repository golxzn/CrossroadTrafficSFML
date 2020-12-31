#pragma once

#include "Cars.h"

class GameComponents {
public:
    GameComponents(int initCarsCount     = GameConstants::initialCarsCount,
                   unsigned windowWidth  = GameConstants::ScreenInfo::WIDTH,
                   unsigned windowHeight = GameConstants::ScreenInfo::HEIGHT);

    bool setBackground(const sf::String &filePath);
    void setCars(const Cars& cars);

    static sf::String defaultBackgroundImgPath();
    sf::Texture backgroundTexture() const;
    sf::Sprite  background()        const;

    Cars mCars;

private:
    sf::Texture mBackgroundTexture;
    sf::Sprite  mBackground;

    unsigned mWindowWidth;
    unsigned mWindowHeight;
};

