#pragma once
#include <stdlib.h>
#include "../Ship/Ship.hpp"
#include <functional>
#include <random>

class AIComponent{
    public:
    AIComponent();
    void update(Ship& ship, float delta);

    private:
    //Random Engine
    std::default_random_engine randEng;

    //Destination tracking
    int x_destination;
    bool destGreaterThanX;

    //Private methods
    void moveShip(Ship& ship, float delta);
    bool reachedDestination(Ship& ship);
    void getNewDestination(Ship& ship);
};