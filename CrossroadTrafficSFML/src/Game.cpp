#include "Game.h"

Game::Game(int initCarsCount, unsigned windowWidth, unsigned windowHeight, const sf::String &title)
    : mComponents(initCarsCount, windowWidth, windowHeight), gamePaused{ true } {
    mWindow.create(sf::VideoMode{windowWidth, windowHeight}, title);
}

Game::~Game() {
    mWindow.close();
}

int Game::start() {
    bool success{ mComponents.setBackground(GameComponents::defaultBackgroundImgPath()) };
    if(!success) {
        return EXIT_FAILURE;
    }

    sf::Event event;
    gamePaused = false;
    while(mWindow.isOpen()) {
        while(mWindow.pollEvent(event)) {
            if(EXIT_SUCCESS == eventHandler(event)) {
                return EXIT_SUCCESS;
            }
        }

        if(!gamePaused) {
            mComponents.mCars.moveCars();
        }

        drawMap();
    }

    return EXIT_SUCCESS;
}

void Game::drawMap() {
    mWindow.clear();

    drawBG();
    drawCars();
    drawUI();

    mWindow.display();
}
void Game::drawBG() {
    mWindow.draw(mComponents.background());
}
void Game::drawCars() {
    for(auto& car : mComponents.mCars) {
        mWindow.draw(*car);
    }

    if(isFururePositionVisable) {
        for(auto& car : mComponents.mCars) {
            Rectangle futureRec{ car->futurePosition() };
            futureRec.setFillColor( sf::Color{ 50, 40, 100, 150 });
            mWindow.draw(futureRec);
        }
    }

}
void Game::drawUI() {
// This method is very dirty, but I think it doesn't matter
// If it was supposed to be better, I'd make an UI class

    sf::Font font;
    font.loadFromFile("res/fonts/UI_font.ttf");

    float fontSize{ 20.0f };
    float paddings{ 10.0f };

    std::vector description{
        sf::Text{
            sf::String{"Press  'Space' to freezing time"},
            font
        },
        sf::Text{
            sf::String{"Press  'V' \t\t to make cars' future positions are visible"},
            font
        },
        sf::Text{
            sf::String{"Press  'Up' \t   to make frame faster"},
            font
        },
        sf::Text{
            sf::String{"Press  'Down' to make frame slower"},
            font
        }
    };

    float panelWidth{ mWindow.getSize().x - paddings * 2 };
    float panelHeight{ (fontSize + paddings) * description.size() };
    sf::RectangleShape Panel{ sf::Vector2f{panelWidth, panelHeight} };

    Panel.setPosition(paddings, paddings);
    Panel.setFillColor(sf::Color{ 40, 30, 40, 70 });

    mWindow.draw(Panel);

    short i{};
    for(auto& line : description) {
        line.setCharacterSize(fontSize);
        line.setPosition(paddings * 2, paddings + (fontSize + paddings) * i++);
        line.setFillColor(sf::Color::White);

        mWindow.draw(line);
    }
}

int Game::eventHandler(const sf::Event &event) {
    if(event.type == sf::Event::Closed) {
        return EXIT_SUCCESS;
    }

    if(event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Space:
                gamePaused = !gamePaused ;
                break;
            case sf::Keyboard::V:
                isFururePositionVisable = !isFururePositionVisable;
                break;
            case sf::Keyboard::Up:
                 mComponents.mCars.makeCarsFaster();
                 break;
            case sf::Keyboard::Down:
                 mComponents.mCars.makeCarsSlower();
                 break;
            default: break;
        }
    }
    return 1;
}
