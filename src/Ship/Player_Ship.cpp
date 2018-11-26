#include "Player_Ship.hpp"

Player_Ship::Player_Ship(Bus& bus, const SpriteSheet& spriteSheet):
Ship{bus, spriteSheet}
{

}

void Player_Ship::update(float timeDelta){
    Ship::update(timeDelta);
    controller.update(*this, timeDelta);
}

void Player_Ship::handleEvent(sf::Event event){
    controller.handleEvent(event);
}