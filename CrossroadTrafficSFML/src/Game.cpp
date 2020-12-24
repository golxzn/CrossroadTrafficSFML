#include "Game.h"

Game::Game(int initCarsCount,
           unsigned windowWidth, unsigned windowHeight,
           const char* title)
    : mComponents(initCarsCount, windowWidth, windowHeight)
{
    mWindow.create(sf::VideoMode{windowWidth, windowHeight}, title);
}

int Game::start() {

    if (!mComponents.setBackground(GameComponents::defaultBackgroundImgPath()))
        return EXIT_FAILURE;

    bool isPaused{ false };

    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                return EXIT_SUCCESS;
            }

            if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        isPaused = !isPaused;
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
        }

        if (!isPaused) mComponents.mCars.moveCars();

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

    for (auto& car : mComponents.mCars)
        mWindow.draw(*car);

    if (isFururePositionVisable) {
        for (auto& car : mComponents.mCars) {
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
    for (auto& line : description) {
        line.setCharacterSize(fontSize);
        line.setPosition(paddings * 2, paddings + (fontSize + paddings) * i++);
        line.setFillColor(sf::Color::White);

        mWindow.draw(line);
    }
}

Game::~Game() {
    mWindow.close();
}
