#include "AI_Ship.hpp"

AI_Ship::AI_Ship(const SpriteSheet& spriteSheet): 
Ship{spriteSheet}
{

}

void AI_Ship::update(float timeDelta){
    Ship::update(timeDelta);
    ai.update(*this, timeDelta);
}