#include "AI_Ship.hpp"

AI_Ship::AI_Ship(Bus& bus, const SpriteSheet& spriteSheet): 
Ship{bus, spriteSheet}
{

}

void AI_Ship::update(float timeDelta){
    Ship::update(timeDelta);
    ai.update(*this, timeDelta);
}