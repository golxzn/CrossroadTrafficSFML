#pragma once

#include "ICar.h"

class ElectroEngineCar : public ICar {
public:
    int  fuel() const      override;
    void refill(int count) override;
    void move()            override;

protected:
    int mCharge;
};

