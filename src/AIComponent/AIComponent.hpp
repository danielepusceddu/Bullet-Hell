#pragma once
#include <stdlib.h>
#include "../Ship/Ship.hpp"
#include <functional>

class AIComponent{
    public:
    AIComponent();
    void update(Ship& ship, float delta);

    private:
    int x_destination;
    bool destGreaterThanX;

    void moveShip(Ship& ship, float delta);
    bool reachedDestination(Ship& ship);
    void getNewDestination(Ship& ship);
};