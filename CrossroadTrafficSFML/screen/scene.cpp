#include "scene.h"

Scene::Scene() {
    using namespace GameConstants::ScreenInfo;

    sf::Texture bgTexture;

    bgTexture.loadFromFile(GameConstants::defaultBackgroundImgPath);

    sf::Vector2u TextureSize{bgTexture.getSize()};

    float ScaleX((float)WIDTH / TextureSize.x);
    float ScaleY((float)HEIGHT / TextureSize.y);

    background.setTexture(bgTexture);
    background.setScale(ScaleX, ScaleY);
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
        case EventType::MakeCarsFaster: cars.makeCarsFaster(); break;
        case EventType::MakeCarsSlower: cars.makeCarsSlower(); break;

        default: break;
    }
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::lock_guard l(carsGuard);
    target.draw(background);
    for(const auto &car : cars) {
        if(nullptr != car) {
            car->draw(target, states);
        }
    }
}

