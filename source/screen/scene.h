#ifndef SCENE_H
#define SCENE_H

#include "platform.h"
#include "eventhandler.h"
#include "Cars.h"

class Scene : public sf::Drawable, public EventReceiver {
public:
    Scene();

protected:
    void onEvent(EventType event) override;
    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
    void update();

private:
    mutable std::mutex carsGuard;
    Cars cars;
    sf::Texture bgTexture;
    sf::Sprite background;
};

#endif // SCENE_H
