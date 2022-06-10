#pragma once

#include "ICar.h"

class GasEngineCar : public ICar {
public:
    int  fuel()      const override;
    void refill(int count) override;

    void move()            override;

private:
    int mFuel{};
};

