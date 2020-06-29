#pragma once

#include "GameComponents.h"


class Game {

public:
    Game(int initCarsCount     = GameConstants::initialCarsCount,
         unsigned windowWidth  = GameConstants::ScreenInfo.WIDTH,
         unsigned windowHeight = GameConstants::ScreenInfo.HEIGHT,
         const char*           = "Game");

    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&)      = delete;

    int start();

    void drawMap();
    void drawBG();
    void drawCars();
    void drawUI();

    ~Game();

private:
    sf::RenderWindow mWindow;
    GameComponents   mComponents;

    bool isFururePositionVisable{ false };

};

