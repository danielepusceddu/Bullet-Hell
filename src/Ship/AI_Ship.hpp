#pragma once
#include "Ship.hpp"
#include "../AIComponent/AIComponent.hpp"

class AI_Ship : public Ship{
    public:
    AI_Ship(Bus& bus, const SpriteSheet& spriteSheet);
    void update(float timeDelta) override;

    private:
    AIComponent ai;
};