#pragma once
#include "Ship.hpp"
#include "../AIComponent/AIComponent.hpp"

class AI_Ship : public Ship{
    public:
    AI_Ship(const SpriteSheet& spriteSheet);
    void update(float timeDelta) override;

    private:
    AIComponent ai;
};