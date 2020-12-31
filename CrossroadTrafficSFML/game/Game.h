#pragma once

#include "GameComponents.h"
#include "screenmgr.h"
#include "scene.h"
#include "userinterface.h"

class Game {
public:
    Game(const sf::String &title = GameConstants::ScreenInfo::TITLE,
         unsigned windowWidth    = GameConstants::ScreenInfo::WIDTH,
         unsigned windowHeight   = GameConstants::ScreenInfo::HEIGHT);

    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&)      = delete;

    int start();

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<UserInterface> UI;

};

