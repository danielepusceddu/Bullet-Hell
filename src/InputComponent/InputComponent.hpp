#pragma once
#include "../Ship/Ship.hpp"

class InputComponent{
    public:
    void update(Ship& ship, float timeDelta);
    void handleEvent(sf::Event event);

    private:
    bool shoot = false;
    bool shootToggle = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
};