#include "screenmgr.h"
#include "scene.h"

Scene::Scene() {
    using namespace GameConstants::ScreenInfo;

    bgTexture.loadFromFile(GameConstants::defaultBackgroundImgPath);
    bgTexture.setSmooth(true);

    sf::Vector2u TextureSize{bgTexture.getSize()};

    float ScaleX((float)WIDTH / TextureSize.x);
    float ScaleY((float)HEIGHT / TextureSize.y);

    background.setTexture(bgTexture);
    background.setScale({ScaleX, ScaleY});
}

void Scene::onEvent(EventType event) {
    switch(event) {
        case EventType::ShowFuturePosition: {
            if(cars.isFuturePositionShowing()) {
                cars.hideFuturePositions();
            } else {
                cars.showFuturePositions();
            }
            break;
        }
        case EventType::MoreCars:
            if(cars.carsCount() < GameConstants::maxCarsCount) {
                std::lock_guard l(carsGuard);
                cars.spawnCarAnywhere();
            }
            break;
        case EventType::LessCars:
            if(cars.carsCount() > GameConstants::minCarsCount) {
                std::lock_guard l(carsGuard);
                cars.removeCarAnywhere();
            }
            break;
        case EventType::Update: update(); break;
        case EventType::MakeCarsFaster: cars.makeCarsFaster(); break;
        case EventType::MakeCarsSlower: cars.makeCarsSlower(); break;

        default: break;
    }
}

void Scene::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    target.draw(background, states);
    std::lock_guard l(carsGuard);
    for(const auto &car : cars) {
        if(nullptr != car) {
            car->draw(target, states);
        }
    }
}

void Scene::update() {
    if(getScreenManager()->isGamePaused()) {
        return;
    }

    std::lock_guard l(carsGuard);
    cars.moveCars();
}

