#include "Ship.hpp"
#include <iostream>

Ship::~Ship() = default;

Ship::Ship(const SpriteSheet& spriteSheet):
GameObject{spriteSheet.texture}, shipAnimation{sprite, spriteSheet.frameWidth}
{
    //test stuff
    shipAnimation.setTimeBetweenFrames(sf::milliseconds(40));
    team = Team::neutral;
    type = Type::none;
}


void Ship::draw(sf::RenderWindow& window){
    window.draw(sprite);
}


void Ship::update(float timeDelta){
    shipAnimation.update(sprite);
}


void Ship::setType(Ship::Type newType){
    type = newType;

    switch(type){
        case Type::mosquito:
        setScale(sf::Vector2f{0.15, 0.15});
        setSpeed(210);
        break;

        case Type::eagle:
        setScale(sf::Vector2f{0.20, 0.20});
        setSpeed(150);
        break;

        case Type::dragon:
        setScale(sf::Vector2f{0.25, 0.25});
        setSpeed(90);
        break;

        default:
        break;
    }
}