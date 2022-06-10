#pragma once

#include "platform.h"

class Rectangle : public sf::RectangleShape {
public:
    Rectangle(float x = 0, float y = 0,
              float width = 0, float height = 0);

   // Position
    float x() const;
    float y() const;

   // Size
    float width() const;
    float height() const;

    bool intersects(const Rectangle& other) const;

};

