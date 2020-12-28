#include "GasEngineCar.h"


int GasEngineCar::fuel() const {
    return mFuel;
}

void GasEngineCar::refill(int count) {
    if(-count <= mFuel) {
        mFuel += count;
    } else {
        mFuel = 0;
    }
}

void GasEngineCar::move() {
    if(mFuel <= 0) {
        return;
    }

    --mFuel;
    ICar::move();
}
