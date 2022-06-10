#include "Game.h"

Game::Game(const sf::String &title, unsigned windowWidth, unsigned windowHeight)
    : scene{ new Scene() }, UI{ new UserInterface() } {
    std::shared_ptr screenmgr = initScreenManager(sf::Vector2u{ windowWidth, windowHeight }, title);
    EventHandler &eh = getEventHandler();
    eh.subscribe(scene);
    eh.subscribe(UI);
    eh.subscribe(screenmgr);

    screenmgr->update(1, scene);
    screenmgr->update(2, UI);
}

int Game::start() {
    getScreenManager()->start();
    getScreenManager()->wait();
    return EXIT_SUCCESS;
}
