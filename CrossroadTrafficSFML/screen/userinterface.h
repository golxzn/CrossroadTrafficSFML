#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "platform.h"
#include "eventhandler.h"

class UserInterface : public sf::Drawable, public EventReceiver {
public:
    UserInterface();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onEvent(EventType event) override;

};

#endif // USERINTERFACE_H
