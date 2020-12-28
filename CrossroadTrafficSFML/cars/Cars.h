#pragma once

#include "platform.h"

#include "GasEngineCar.h"
#include "ElectroEngineCar.h"
#include "HybridEngineCar.h"

#include "GameConstants.h"

class Cars {

    using CarsContainer = std::vector<std::unique_ptr<ICar>>;
    using Dir           = ICar::eDirection;

public:
    Cars(int initCarsCount     = GameConstants::initialCarsCount,
         unsigned windowWidth  = GameConstants::ScreenInfo.WIDTH,
         unsigned windowHeight = GameConstants::ScreenInfo.HEIGHT);

    Cars(const Cars&)            = delete;
    Cars(Cars&&)                 = delete;
    Cars& operator=(const Cars&) = delete;
    Cars& operator=(Cars&&)      = delete;

    void moveCars();

    void makeCarsFaster();
    void makeCarsSlower();

    void spawnCarFromTop();
    void spawnCarFromBottom();
    void spawnCarFromLeft();
    void spawnCarFromRight();

    void spawnCarAnywhere();

    CarsContainer::iterator begin();
    CarsContainer::iterator end();

    CarsContainer::const_iterator cbegin() const;
    CarsContainer::const_iterator cend()   const;

    ~Cars();

private:
    CarsContainer mCarsCont;
    float         mCarsSpeed{ GameConstants::defaultSpeed };

    unsigned mWindowWidth;
    unsigned mWindowHeight;

    void replaceOutOfScreenCars();
    int  getRandomNumber(int start, int end)                         const;
    bool checkFutureIntersect(const ICar& first, const ICar& second) const;
    bool intoOncomingCar(const ICar& first, const ICar& second)      const;

    void createRandomCar(Dir direction =         GameConstants::defaultDirection,
                         const Rectangle& rect = GameConstants::defaultCarRectangle,
                         float speed = GameConstants::defaultSpeed,
                         int   fuel  = GameConstants::defaultFuel,
                         float range = GameConstants::defaultRange);

};

