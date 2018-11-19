#include "Ship.hpp"
#include <iostream>

Ship::~Ship() = default;

Ship::Ship(Bus& bus, const SpriteSheet& spriteSheet):
BusWriter{bus}, GameObject{spriteSheet.texture}, shipAnimation{sprite, spriteSheet.frameWidth}
{
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


bool Ship::shoot(){
    bool shot;

    if(isReadyToShoot()){
        sf::Time now = clock.getElapsedTime();
        sendMessage(Message{Message::Type::SHIP_SHOT, *this});
        lastShot = now;
        shot = true;
    }

    else shot = false;

    return shot;
}


bool Ship::isReadyToShoot(){
    if(readyToShoot == false){
        sf::Time now = clock.getElapsedTime();
        readyToShoot = (now - timeBetweenShots) >= lastShot;
    }

    return readyToShoot;
}


void Ship::setMinTimeBetweenShots(sf::Time time){
    timeBetweenShots = time;
}


void Ship::setTeam(Ship::Team newTeam){
    team = newTeam;
}


Ship::Team Ship::getTeam(){
    return team;
}


Ship::Type Ship::getType(){
    return type;
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