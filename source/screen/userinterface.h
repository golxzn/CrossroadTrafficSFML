#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "platform.h"
#include "eventhandler.h"

class UserInterface : public sf::Drawable, public EventReceiver {
public:
    UserInterface();

protected:
    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void onEvent(EventType event) override;

private:
    float fontSize;
    float paddings;
    sf::Font font;
    std::vector<sf::Text> description;
    sf::Vector2f panelSize;
    sf::RectangleShape panel;

};

#endif // USERINTERFACE_H
