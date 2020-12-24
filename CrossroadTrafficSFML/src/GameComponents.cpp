#include "GameComponents.h"


GameComponents::GameComponents(int initCarsCount,
                               unsigned windowWidth, unsigned windowHeight)
    : mCars{ initCarsCount, windowWidth, windowHeight },
      mWindowWidth{ windowWidth },
      mWindowHeight{ windowHeight }
{}

bool GameComponents::setBackground(const char* filePath) {
    if (!mBackgroundTexture.loadFromFile(filePath))
        return false;

    sf::Vector2u TextureSize{ mBackgroundTexture.getSize() };
    sf::Vector2u WindowSize{ mWindowWidth, mWindowHeight };

    float ScaleX{ static_cast<float>(WindowSize.x) / TextureSize.x };
    float ScaleY{ static_cast<float>(WindowSize.y) / TextureSize.y };

    mBackground.setTexture(mBackgroundTexture);
    mBackground.setScale(ScaleX, ScaleY);

    return true;
}

sf::Sprite GameComponents::background() const {
    return mBackground;
}

sf::Texture GameComponents::backgroundTexture() const {
    return mBackgroundTexture;
}


