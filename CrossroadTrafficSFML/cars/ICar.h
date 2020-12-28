#pragma once

#include <Rectangle.h>

class ICar : public sf::Drawable {
public:
    enum class eDirection : short {
        UP,
        LEFT,
        RIGHT,
        DOWN
    };

    Rectangle futurePosition()                 const;
    bool haveToPassOtherCar(const ICar& other) const;
    bool isInScreen(float width, float height) const;

    virtual void move();
    virtual int  fuel()      const = 0;
    virtual void refill(int count) = 0;

    virtual ~ICar() = default;

   // Getters
    Rectangle   rect() const;
    eDirection   dir() const;
    float      speed() const;
    float      range() const;

   // Setters
    void setRect(const Rectangle& rect);
    void setDir(const eDirection& dir);
    void setSpeed(float speed);
    void setRange(float range);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


protected:
    Rectangle  mRect;
    eDirection mDir;
    float      mSpeed{};
    float      mRange{};
};

