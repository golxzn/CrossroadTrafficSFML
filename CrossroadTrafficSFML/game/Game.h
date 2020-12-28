#pragma once

#include "GameComponents.h"

class Game {
public:
    Game(int initCarsCount       = GameConstants::initialCarsCount,
         unsigned windowWidth    = GameConstants::ScreenInfo.WIDTH,
         unsigned windowHeight   = GameConstants::ScreenInfo.HEIGHT,
         const sf::String &title = "Game");

    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&)      = delete;

    ~Game();

    int start();

    void drawMap();
    void drawBG();
    void drawCars();
    void drawUI();

private:
    sf::RenderWindow mWindow;
    GameComponents   mComponents;
    bool gamePaused;

    bool isFururePositionVisable{ false };

    int eventHandler(const sf::Event &event);

};

