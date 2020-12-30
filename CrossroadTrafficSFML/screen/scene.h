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
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Cars cars;
    sf::Sprite background;
};

#endif // SCENE_H
