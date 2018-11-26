#pragma once
#include "Ship.hpp"
#include "../InputComponent/InputComponent.hpp"

class Player_Ship : public Ship{
    public:
    Player_Ship(Bus& bus, const SpriteSheet& spriteSheet);
    void update(float timeDelta) override;
    void handleEvent(sf::Event event);

    private:
    InputComponent controller;
};