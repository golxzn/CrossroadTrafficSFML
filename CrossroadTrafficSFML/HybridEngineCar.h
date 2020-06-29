#pragma once

#include "ICar.h"

class HybridEngineCar : public ICar {
public:
    int  fuel() const      override;
    void refill(int count) override;
    void move()            override;

protected:
    int mFuel{};
    int mCharge{};
};

