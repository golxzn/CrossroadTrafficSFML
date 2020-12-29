#include "screenmgr.h"

//=============================== ScreenManager ===============================//

ScreenManager::ScreenManager(const sf::Vector2u &size, const sf::String &title) {
    screen.create(sf::VideoMode{size.x, size.y}, title);
}

void ScreenManager::addTarget(DrawablePtr target) {
    std::vector<DrawablePtr>::const_iterator found = find(target->first);

    if(found == drawTargets.end()) {
        drawTargets.emplace_back(target);
        handler.update(target);
    }
}

void ScreenManager::removeTarget(id_t targetID) {
    std::vector<DrawablePtr>::const_iterator found = find(targetID);
    if(found != drawTargets.end()) {
        drawTargets.erase(found);
        handler.rmTarget(found);
    }
}

void ScreenManager::start() {
    if(nullptr != drawThread) {
        return;
    }
    handler.start();

    drawThread.reset(new std::thread(drawloop, handler));
}

void ScreenManager::end() {
    if(nullptr == drawThread) {
        return;
    }
    handler.stop();
    drawThread->join();
}

std::vector<DrawablePtr>::const_iterator ScreenManager::find(id_t id) const {
    return std::find_if(drawTargets.begin(), drawTargets.end(),
        [&id](DrawablePtr ent) -> bool {
            return ent->first == id;
        });
}

void ScreenManager::drawloop(ScreenManager::ThreadHandler &handler) {
    while(handler.isRunning()) {
        // draw stuff
    }
}

//=============================== ThreadHandler ===============================//


ScreenManager::ThreadHandler::ThreadHandler()
    : running{ false } {
}

void ScreenManager::ThreadHandler::rmTarget(std::vector<DrawablePtr>::const_iterator rmTarget) {
    std::lock_guard<std::mutex> l(targetsGuard);
    targets.erase(rmTarget);
}

void ScreenManager::ThreadHandler::update(DrawablePtr drawTarget) {
    std::lock_guard<std::mutex> l(targetsGuard);
    targets.emplace_back(drawTarget);
}

void ScreenManager::ThreadHandler::start() {
    std::lock_guard<std::mutex> l(targetsGuard);
    running = true;
}

void ScreenManager::ThreadHandler::stop() {
    std::lock_guard<std::mutex> l(targetsGuard);
    running = false;
}

bool ScreenManager::ThreadHandler::isRunning() const {
    return running;
}

std::vector<DrawablePtr> ScreenManager::ThreadHandler::getTargets() const {
    return targets;
}
