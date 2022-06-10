#include "HybridEngineCar.h"

int HybridEngineCar::fuel() const {
    return mFuel + mCharge;
}

void HybridEngineCar::refill(int count) {
    if (-count / 2 <= mFuel) {
        mFuel += count / 2;
        count /= 2;
    }
    if (-count <= mCharge) {
        mCharge += count;
    }
}

void HybridEngineCar::move() {
    if (mFuel > mCharge && mFuel > 0){
        --mFuel;
        ICar::move();
    } else if (mCharge > 0) {
        --mCharge;
        ICar::move();
    }
}
