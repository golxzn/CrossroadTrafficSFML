#include "screenmgr.h"

ScreenManager &initScreenManager(const sf::Vector2u &size, const sf::String &title) {
    ScreenManager &mgr = getScreenManager();
    mgr.init(size, title);
    return mgr;
}

ScreenManager &getScreenManager() {
    return ScreenManager::instance();
}

//=============================== ScreenManager ===============================//

void ScreenManager::init(const sf::Vector2u &size, const sf::String &title) {
    if(screen.isOpen()) {
        return;
    }
    screen.create(sf::VideoMode{size.x, size.y}, title);
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
        targetsGuard.lock();
        drawTargets.erase(found);
        targetsGuard.unlock();
    }
}

void ScreenManager::start() {
    if(nullptr != drawThread) {
        return;
    }
    handler.start();

    drawThread.reset(new std::thread(drawloop, std::ref(handler)));
}

void ScreenManager::end() {
    if(nullptr == drawThread) {
        return;
    }
    handler.stop();
    drawThread->join();
}

GuardedScreen ScreenManager::getScreen() {
    return std::make_pair(std::ref(screenGuard), std::ref(screen));
}

GuardedTargets ScreenManager::getTargets() {
    return std::make_pair(std::ref(targetsGuard), std::ref(drawTargets));
}

std::map<id_t, DrawablePtr>::const_iterator ScreenManager::find(id_t id) const {
    return std::find_if(drawTargets.begin(), drawTargets.end(),
        [&id](const std::pair<id_t, DrawablePtr> &ent) -> bool {
            return ent.first == id;
        });
}

void ScreenManager::drawloop(ScreenManager::ThreadHandler &handler) {
    GuardedScreen screen = getScreenManager().getScreen();
    GuardedTargets targets = getScreenManager().getTargets();
    auto update = [&]() {
        GuardedTargets updated = getScreenManager().getTargets();
        // only if we have old version of targets and it's unlock
        if(targets.second.size() != updated.second.size() && targets.first.try_lock()) {
            targets.second = updated.second;
        }
    };
    auto redraw = [&screen, &targets](const sf::Color &bgclr = sf::Color::White) {
        sf::RenderWindow &win = screen.second;
        std::map<id_t, DrawablePtr> obgs = targets.second;

        int lockedId = std::try_lock(screen.first, targets.first);
        if(0 != lockedId) {
            return;
        }

        win.clear(bgclr);
        for(auto& it : obgs) {
            win.draw(*(it.second));
        }
        win.display();
    };

    sf::Clock delta;
    sf::Event event;
    while(handler.isRunning()) {
        if(!screen.second.isOpen()) {
            continue;
        }
        while(screen.second.pollEvent(event)) {
            getEventHandler().pull(event);
        }
        update();
        redraw();
    }
}

void ScreenManager::onEvent(EventType type) {
    switch(type) {
        case EventType::CloseApplication: {
            std::lock_guard l(screenGuard);
            handler.stop();
            screen.close();
            return;
        }
        case EventType::PauseGame: {
            // pause game
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

