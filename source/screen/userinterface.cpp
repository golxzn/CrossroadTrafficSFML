#include "GameConstants.h"
#include "userinterface.h"

UserInterface::UserInterface()
    : fontSize{ 20.0f }, paddings{ 10.0f } {

    font.loadFromFile(GameConstants::defaultUIFontPath);

    description = std::vector<sf::Text>{
        sf::Text{ sf::String{"Press  'Escape' to freezing time"}, font },
        sf::Text{ sf::String{"Press  'V' to make cars' future positions are visible"}, font },
        sf::Text{ sf::String{"Press  'Up' to make frame faster"}, font },
        sf::Text{ sf::String{"Press  'Down' to make frame slower"}, font },
        sf::Text{ sf::String{"Press  '+' to add new car in scene"}, font },
        sf::Text{ sf::String{"Press  '-' to remove one car from scene"}, font }
    };
    panelSize = { GameConstants::ScreenInfo::WIDTH - paddings * 2,
                  (fontSize + paddings) * description.size() };
    panel = sf::RectangleShape{ panelSize };
    panel.setPosition({paddings, paddings});
    panel.setFillColor( GameConstants::defaultPanelColor );

    short i{};
    for(auto &line : description) {
        line.setCharacterSize(fontSize);
        line.setPosition({paddings * 2, paddings + (fontSize + paddings) * i++});
        line.setFillColor(sf::Color::White);
    }
}

void UserInterface::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    target.draw(panel, states);
    for(const auto &line : description) {
        target.draw(line, states);
    }
}

void UserInterface::onEvent(EventType event) {
    (void)(event);
}
