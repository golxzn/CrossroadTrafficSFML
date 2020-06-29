#include "ICar.h"

Rectangle ICar::futurePosition() const {
    Rectangle futureRectanglePosition {
        mRect.x() - mRange / 2, mRect.y() - mRange / 2,
        mRect.width() + mRange, mRect.height() + mRange
    };

    switch (mDir) {
        case eDirection::UP:
            futureRectanglePosition.move(.0f, -mSpeed);
            break;

        case eDirection::DOWN:
            futureRectanglePosition.move(.0f, mSpeed);
            break;

        case eDirection::LEFT:
            futureRectanglePosition.move(-mSpeed, .0f);
            break;

        case eDirection::RIGHT:
            futureRectanglePosition.move(mSpeed, .0f);
            break;
    }

    return futureRectanglePosition;
}

bool ICar::haveToPassOtherCar(const ICar& other) const {
    using Dir = eDirection;

    auto otherDir{ other.mDir };

// Pass car in front of
    if (mDir == otherDir) {
        switch (mDir) {
            case Dir::UP:
                return mRect.y() > other.rect().y();

            case Dir::DOWN:
                return mRect.y() < other.rect().y();

            case Dir::RIGHT:
                return mRect.x() < other.rect().x();

            case Dir::LEFT:
                return mRect.x() > other.rect().x();

        }
    }

// Pass car from right
    if (mDir == Dir::UP && otherDir == Dir::LEFT &&
        mRect.y() > other.mRect.y() + other.mRect.height())
        return true;

    if (mDir == Dir::DOWN && otherDir == Dir::RIGHT &&
        mRect.y() + mRect.height() < other.mRect.y())
        return true;

    if (mDir == Dir::RIGHT && otherDir == Dir::UP &&
        mRect.x() + mRect.width() < other.mRect.x())
        return true;

    if (mDir == Dir::LEFT && otherDir == Dir::DOWN &&
        mRect.x() > other.mRect.x() + other.mRect.width())
        return true;

// Pass car from left who already into the crossroad
    if (mDir == Dir::UP && otherDir == Dir::RIGHT &&
        mRect.x() < other.mRect.x() + other.mRect.width())
        return true;

    if (mDir == Dir::DOWN && otherDir == Dir::LEFT &&
        mRect.x() + mRect.width() > other.mRect.x())
        return true;

    if (mDir == Dir::RIGHT && otherDir == Dir::DOWN &&
        mRect.y() < other.mRect.y() + other.mRect.height())
        return true;

    if (mDir == Dir::LEFT && otherDir == Dir::UP &&
        mRect.y() + mRect.height() > other.mRect.y())
        return true;

    return false;
}

bool ICar::isInScreen(float width, float height) const {
    return (mRect.x() + mRect.width()  > 0 && mRect.x() < width) &&
           (mRect.y() + mRect.height() > 0 && mRect.y() < height);
}

void ICar::move() {
    switch (mDir) {
        case eDirection::UP:
            mRect.move(.0f, -mSpeed);
            break;

        case eDirection::DOWN:
            mRect.move(.0f, mSpeed);
            break;

        case eDirection::LEFT:
            mRect.move(-mSpeed, .0f);
            break;

        case eDirection::RIGHT:
            mRect.move(mSpeed, .0f);
            break;
    }
}

Rectangle ICar::rect() const {
    return mRect;
}

void ICar::setRect(const Rectangle& rect) {
    mRect = rect;
}

ICar::eDirection ICar::dir() const {
    return mDir;
}

void ICar::setDir(const eDirection& dir) {
    mDir = dir;
}

float ICar::speed() const {
    return mSpeed;
}

void ICar::setSpeed(float speed) {
    mSpeed = speed;
}

void ICar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // There's we can make the textures and other visualisations details
    sf::RectangleShape rect{ mRect };
    rect.setFillColor(sf::Color::Green);
    target.draw(rect, states);
}

float ICar::range() const {
    return mRange;
}

void ICar::setRange(float range) {
    mRange = range;
}
