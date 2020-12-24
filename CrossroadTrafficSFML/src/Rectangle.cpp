#include "Rectangle.h"


Rectangle::Rectangle(float x, float y, float width, float height) {
    this->setPosition(sf::Vector2f{x, y});
    this->setSize(sf::Vector2f{width, height});
}

float Rectangle::x() const {
    return this->getPosition().x;
}

float Rectangle::y() const {
    return this->getPosition().y;
}

float Rectangle::width() const {
    return this->getSize().x;
}

float Rectangle::height() const {
    return this->getSize().y;
}

bool Rectangle::intersects(const Rectangle& other) const {
    // it's impossible to intersect with itself
    if (this == &other) {
        return false;
    }

    return (x() <= other.x() + other.width()  && x() + width()  >= other.x()) &&
           (y() <= other.y() + other.height() && y() + height() >= other.y());
}
