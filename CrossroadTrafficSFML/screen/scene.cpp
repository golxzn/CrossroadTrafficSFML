#include "scene.h"

Scene::Scene()
{
    using namespace GameConstants::ScreenInfo;

    sf::Texture bgTexture;

    bgTexture.loadFromFile(GameConstants::defaultBackgroundImgPath);

    sf::Vector2u TextureSize{bgTexture.getSize()};
    sf::Vector2u WindowSize{WIDTH, HEIGHT};

    float ScaleX(WIDTH / TextureSize.x);
    float ScaleY(HEIGHT / TextureSize.y);

    background.setTexture(bgTexture);
    background.setScale(ScaleX, ScaleY);
}

void Scene::onEvent(EventType event) {
    switch(event) {
        case EventType::MakeCarsFaster:
            cars.makeCarsFaster();
            break;
        case EventType::MakeCarsSlower:
            cars.makeCarsSlower();
            break;
        case EventType::ShowFuturePosition:
            if(cars.isFuturePositionShowing()) {
                cars.hideFuturePositions();
            } else {
                cars.showFuturePositions();
            }
            break;
        default: break;
    }
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    for (auto &car : cars)
    {
        car->draw(target, states);
    }
}
