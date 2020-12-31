#include "GameConstants.h"
#include "userinterface.h"

UserInterface::UserInterface() {

}

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Font font;
    font.loadFromFile(GameConstants::defaultUIFontPath);

    float fontSize{ 20.0f };
    float paddings{ 10.0f };

    std::vector description{
        sf::Text{ sf::String{"Press  'Escape' to freezing time"}, font },
        sf::Text{ sf::String{"Press  'V' to make cars' future positions are visible"}, font },
        sf::Text{ sf::String{"Press  'Up' to make frame faster"}, font },
        sf::Text{ sf::String{"Press  'Down' to make frame slower"}, font },
        sf::Text{ sf::String{"Press  '+' to add new car in scene"}, font },
        sf::Text{ sf::String{"Press  '-' to remove one car from scene"}, font }
    };

    float panelWidth{ GameConstants::ScreenInfo::WIDTH - paddings * 2 };
    float panelHeight{ (fontSize + paddings) * description.size() };
    sf::RectangleShape Panel{ sf::Vector2f{panelWidth, panelHeight} };

    Panel.setPosition(paddings, paddings);
    Panel.setFillColor(sf::Color{ 40, 30, 40, 70 });

    target.draw(Panel, states);

    short i{};
    for(auto& line : description) {
        line.setCharacterSize(fontSize);
        line.setPosition(paddings * 2, paddings + (fontSize + paddings) * i++);
        line.setFillColor(sf::Color::White);

        target.draw(line, states);
    }
}

void UserInterface::onEvent(EventType event) {
    (void)(event);
}
