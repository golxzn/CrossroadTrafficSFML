#include "screenmgr.h"

std::shared_ptr<ScreenManager> initScreenManager(const sf::Vector2u &size, const sf::String &title) {
    std::shared_ptr<ScreenManager> mgr = getScreenManager();
    mgr->init(size, title);
    return mgr;
}

//ScreenManager &getScreenManager() {
//    return ScreenManager::instance();
//}

std::shared_ptr<ScreenManager> getScreenManager() {
    return ScreenManager::instancePtr();
}

//=============================== ScreenManager ===============================//

void ScreenManager::init(const sf::Vector2u &size, const sf::String &title) {
    if(nullptr == screen) {
        screen.reset(new sf::RenderWindow());
    }
    if(screen->isOpen()) {
        return;
    }
    screen->create(sf::VideoMode{size.x, size.y}, title);
    screen->clear(sf::Color::White);
    screen->display();
}

void ScreenManager::update(id_t id, DrawablePtr target) {
    if(nullptr == target) {
        return;
    }
    std::lock_guard l(targetsGuard);
    drawTargets[id] = target;
}

void ScreenManager::removeTarget(id_t targetID) {
    std::map<id_t, DrawablePtr>::const_iterator found = find(targetID);
    if(found != drawTargets.end()) {
        std::lock_guard l(targetsGuard);
        drawTargets.erase(found);
    }
}

void ScreenManager::start() {
    if(nullptr != drawThread) {
        return;
    }
    handler.start();

    drawThread.reset(new std::thread(drawloop, std::ref(handler)));
}

void ScreenManager::stop() {
    if(nullptr == drawThread) {
        return;
    }
    handler.stop();
    // make sure we're single owner of screen
    while(screen.use_count() != 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::lock_guard l(screenGuard);
    screen->close();
}

void ScreenManager::wait() {
    drawThread->join();
}

GuardedScreen ScreenManager::getScreen() {
    return std::make_pair(std::ref(screenGuard), screen);
}

GuardedTargets ScreenManager::getTargets() {
    return std::make_pair(std::ref(targetsGuard), std::ref(drawTargets));
}

bool ScreenManager::isGamePaused() const {
    return handler.isPaused();
}

std::map<id_t, DrawablePtr>::const_iterator ScreenManager::find(id_t id) const {
    return std::find_if(drawTargets.begin(), drawTargets.end(),
        [&id](const std::pair<id_t, DrawablePtr> &ent) -> bool {
            return ent.first == id;
        });
}

void ScreenManager::drawloop(ScreenManager::ThreadHandler &handler) {
    GuardedScreen screen = getScreenManager()->getScreen();
    GuardedTargets targets = getScreenManager()->getTargets();
    auto update = [&]() {
        const auto &updated = getScreenManager()->getTargets().second;
        auto &current = targets.second;
        auto &curGuard = targets.first;
        // only if we found new or removed target and it's unlock
        if(current.size() != updated.size() && curGuard.try_lock()) {
            curGuard.lock();
            current = updated;
        }
    };

    auto redraw = [&screen, &targets](const sf::Color &bgclr = sf::Color::White) {
        std::shared_ptr<sf::RenderWindow> win = screen.second;
        std::map<id_t, DrawablePtr> obgs = targets.second;

        std::lock_guard l(screen.first);
        win->clear(bgclr);
        for(auto& it : obgs) {
            win->draw(*(it.second));
        }
        win->display();
    };

    sf::Event event;
    while(handler.isRunning()) {
        if(!screen.second->isOpen()) {
            continue;
        }
        while(screen.second->pollEvent(event)) {
            getEventHandler().pull(event);
        }
        getEventHandler().pull(EventType::Update);
        update();
        redraw();
    }
}

void ScreenManager::onEvent(EventType type) {
    switch(type) {
        case EventType::CloseApplication: {
            stop();
            return;
        }
        case EventType::PauseGame: {
            if(!isGamePaused()) {
                handler.pause();
            } else {
                handler.resume();
            }
        }
        default: return;
    }
}

//=============================== ThreadHandler ===============================//

void ScreenManager::ThreadHandler::start() {
    running = true;
}

void ScreenManager::ThreadHandler::stop() {
    running = false;
}

void ScreenManager::ThreadHandler::pause() {
    paused = true;
}

void ScreenManager::ThreadHandler::resume() {
    paused = false;
}

bool ScreenManager::ThreadHandler::isRunning() const {
    return running;
}

bool ScreenManager::ThreadHandler::isPaused() const {
    return paused;
}

