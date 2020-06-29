#include "ElectroEngineCar.h"


int ElectroEngineCar::fuel() const {
    return mCharge;
}

void ElectroEngineCar::refill(int count) {
    if ( -count <= mCharge)
        mCharge += count;
    else
        mCharge = 0;
}

void ElectroEngineCar::move() {
    if (mCharge <= 0)
        return;

    --mCharge;
    ICar::move();
}
