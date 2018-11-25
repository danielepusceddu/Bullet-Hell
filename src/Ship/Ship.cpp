#include "Ship.hpp"

Ship::~Ship() = default;

Ship::Ship(Bus& bus, const SpriteSheet& spriteSheet):
GameObject{spriteSheet.texture}, BusWriter{bus}, shipAnimation{sprite, spriteSheet.frameWidth}
{
    shipAnimation.setTimeBetweenFrames(sf::milliseconds(40));
    team = Team::neutral;
    type = Type::none;
}


void Ship::update(float timeDelta){
    shipAnimation.update(sprite);
}


void Ship::draw(sf::RenderWindow& window){
    GameObject::draw(window);
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


void Ship::damage(int dmg){
    if(dead == false){
        health -= dmg;
        if(health <= 0){
            dead = true;
            sendMessage(Message{Message::Type::SHIP_DEATH, *this});
        }
    }
}

bool Ship::isDead() const{
    return dead;
}


void Ship::setMinTimeBetweenShots(sf::Time time){
    timeBetweenShots = time;
}


void Ship::setTeam(Ship::Team newTeam){
    team = newTeam;
}


Ship::Team Ship::getTeam() const{
    return team;
}


Ship::Type Ship::getType() const{
    return type;
}


void Ship::setType(Ship::Type newType){
    type = newType;

    switch(type){
        case Type::mosquito:
        setScale(sf::Vector2f{0.15, 0.15});
        setSpeed(210);
        health = 15;
        break;

        case Type::eagle:
        setScale(sf::Vector2f{0.20, 0.20});
        setSpeed(150);
        health = 20;
        break;

        case Type::dragon:
        setScale(sf::Vector2f{0.25, 0.25});
        setSpeed(90);
        health = 30;
        break;

        default:
        break;
    }
}