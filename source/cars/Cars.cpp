#include "Cars.h"


Cars::Cars(int initCarsCount, unsigned windowWidth, unsigned windowHeight)
    : mWindowWidth{ windowWidth }, mWindowHeight{ windowHeight } {
    mCarsCont.reserve(initCarsCount);

    for(int i{}; i < initCarsCount; ++i) {
        spawnCarAnywhere();
    }
}

void Cars::moveCars() {
    for(auto& car : mCarsCont) {
        bool canCarMove{ true };

        for(auto& other : mCarsCont) {
            if(car == other || intoOncomingCar(*car, *other)) {
                continue;
            }

            if(checkFutureIntersect(*car, *other) &&
                car->haveToPassOtherCar(*other)) {
                canCarMove = false;
                break;
            }
        }

        if(canCarMove) {
            car->move();
        }
    }

    replaceOutOfScreenCars();
}

void Cars::makeCarsFaster() {
    if(mCarsSpeed > GameConstants::maxCarSpeed) {
        return;
    }
    mCarsSpeed += GameConstants::defaultSpeedChain;

    for(auto& car : mCarsCont) {
        car->setSpeed(mCarsSpeed);
    }
}

void Cars::makeCarsSlower() {
    if(mCarsSpeed < GameConstants::minCarSpeed) {
        return;
    }
    mCarsSpeed -= GameConstants::defaultSpeedChain;

    for(auto& car : mCarsCont) {
        car->setSpeed(mCarsSpeed);
    }
}

void Cars::spawnCarFromTop() {
    using namespace GameConstants;

    Rectangle rect {
        mWindowWidth / 2.0f - defaultCarWidth - centreStrip,
        0.0f,
        defaultCarWidth,
        defaultCarHeight
    };

    createRandomCar(Dir::DOWN, rect, mCarsSpeed);
}

void Cars::spawnCarFromBottom() {
    using namespace GameConstants;

    Rectangle rect{
        mWindowWidth / 2.0f + centreStrip,
        static_cast<float>(mWindowHeight - defaultCarHeight),
        defaultCarWidth,
        defaultCarHeight
    };

    createRandomCar(Dir::UP, rect, mCarsSpeed);
}

void Cars::spawnCarFromLeft() {
    using namespace GameConstants;

    Rectangle rect{
        0,
        static_cast<float>(mWindowHeight) / 2.0f + centreStrip,
        defaultCarHeight,
        defaultCarWidth
    };

    createRandomCar(Dir::RIGHT, rect, mCarsSpeed);
}

void Cars::spawnCarFromRight() {
    using namespace GameConstants;

    Rectangle rect{
        static_cast<float>(mWindowWidth - defaultCarHeight),
        static_cast<float>(mWindowHeight) / 2.0f - defaultCarWidth - centreStrip,
        defaultCarHeight,
        defaultCarWidth
    };

    createRandomCar(Dir::LEFT, rect, mCarsSpeed);
}

void Cars::spawnCarAnywhere() {
    switch(getRandomNumber(1, 4)) {
        case 1:
            spawnCarFromRight();
            break;
        case 2:
            spawnCarFromTop();
            break;
        case 3:
            spawnCarFromBottom();
            break;
        case 4:
            spawnCarFromLeft();
            break;
    }
}

void Cars::removeCarAnywhere() {
    if(mCarsCont.empty()) {
        return;
    }
    const int removing_position{ getRandomNumber(0, mCarsCont.size() - 1) };

    mCarsCont.erase(mCarsCont.begin() + removing_position);
}

size_t Cars::carsCount() const {
    return mCarsCont.size();
}

bool Cars::isFuturePositionShowing() const {
    return currentFuturePosVisability;
}

void Cars::showFuturePositions() {
    currentFuturePosVisability = true;
    for(auto car{ mCarsCont.begin() }; car != mCarsCont.end(); ++car) {
        car->get()->showFuturePosition();
    }
}

void Cars::hideFuturePositions() {
    currentFuturePosVisability = false;
    for(auto car{ mCarsCont.begin() }; car != mCarsCont.end(); ++car) {
        car->get()->hideFuturePosition();
    }
}

CarsContainer::iterator Cars::begin() {
    return mCarsCont.begin();
}

CarsContainer::iterator Cars::end() {
    return mCarsCont.end();
}

CarsContainer::const_iterator Cars::begin() const {
    return mCarsCont.cbegin();
}

CarsContainer::const_iterator Cars::end() const {
    return mCarsCont.cend();
}

Cars::~Cars() {
    mCarsCont.clear();
}

void Cars::replaceOutOfScreenCars() {
    using namespace GameConstants;

    for(auto car{ mCarsCont.begin() }; car != mCarsCont.end(); ++car) {
        if(!(*car)->isInScreen(ScreenInfo::WIDTH, ScreenInfo::HEIGHT)) {
            car = mCarsCont.erase(car);
            spawnCarAnywhere();
        }
    }
}

int Cars::getRandomNumber(int start, int end) const {
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    int result{ start + rand() % end };
    return result;
}

bool Cars::checkFutureIntersect(const ICar& first,
                                const ICar& second) const {
    if(first.dir() == second.dir()) {
        return first.futurePosition().intersects(second.rect());
    }

    const Rectangle& firstFutPos{ first.futurePosition() };
    const Rectangle& seconFutPos{ second.futurePosition() };

    bool result{ firstFutPos.intersects(seconFutPos) };
    return result;
}

bool Cars::intoOncomingCar(const ICar& first, const ICar& second) const {
    return (first.dir() == Dir::DOWN  && second.dir() == Dir::UP)   ||
           (first.dir() == Dir::LEFT  && second.dir() == Dir::RIGHT)||
           (first.dir() == Dir::RIGHT && second.dir() == Dir::LEFT) ||
           (first.dir() == Dir::UP    && second.dir() == Dir::DOWN) ;
}

void Cars::createRandomCar(Dir direction, const Rectangle& rect,
                           float speed, int fuel, float range) {
    switch(getRandomNumber(1, 3)) {
        case 1:
            mCarsCont.emplace_back(std::make_unique<GasEngineCar>());
            break;
        case 2:
            mCarsCont.emplace_back(std::make_unique<ElectroEngineCar>());
            break;
        case 3:
            mCarsCont.emplace_back(std::make_unique<HybridEngineCar>());
            break;
    }

    auto& newCar = mCarsCont.back();
    newCar->setDir(direction);
    newCar->setRect(rect);
    newCar->setSpeed(speed);
    newCar->setRange(range);
    newCar->refill(fuel);
    if(currentFuturePosVisability) {
        newCar->showFuturePosition();
    }

}
