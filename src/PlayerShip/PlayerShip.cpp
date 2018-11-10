#include "PlayerShip.hpp"
#include "../../extlibs/Collision/Collision.h"

//****************
//*PUBLIC METHODS*
//****************


void Player_Ship::setHealth(int health){
    this->health = health;
}


void Player_Ship::damage(int dmg){
    if(dead == false){
        health -= dmg;

        if(health <= 0){
            dead = true;
            bus.get().sendMessage(Message{Message::Type::SHIP_DEATH, *this});
        }
    }
}


//Shoot method. Returns vector of bullets
std::vector<sf::Sprite> Player_Ship::shoot(){
    sf::Time elapsed = clock.getElapsedTime();
    std::vector<sf::Sprite> shots;

    //If enough time has passed
    if(elapsed.asMilliseconds() - lastShot >= msBetweenShots){
        sf::FloatRect bulletRect = bulletSprite.getGlobalBounds();
        sf::Vector2f shipPos = getPos();

        //Place a bullet on each shooting point
        for(sf::Vector2f shootingPoint : shootingPoints){
            bulletSprite.setPosition(shootingPoint.x - bulletRect.width / 2, shootingPoint.y - bulletRect.height);
            bulletSprite.move(shipPos);
            shots.push_back(bulletSprite);
        }

        //Update time of last shot
        lastShot = elapsed.asMilliseconds();

        //Send Shot Event
        Message::Type type = (_team == Player_Ship::Team::blue) ? Message::Type::BLUE_SHIP_SHOT : Message::Type::RED_SHIP_SHOT;
        bus.get().sendMessage(Message{type, *this});
    }

    //Return vector of bullets
    return shots;
}


void Player_Ship::initShipType(ShipTypes type){
    switch(type){
        case ShipTypes::eagle:
        initEagle();
        break;

        case ShipTypes::mosquito:
        initMosquito();
        break;

        case ShipTypes::dragon:
        initDragon();
        break;
    }
}

void Player_Ship::flipVertically(){
    Animation::flipVertically();    //Do default Animation flip

    //Get center of the ship
    sf::FloatRect shipRect = getRect();
    sf::Vector2f shipCenter = {shipRect.width / 2, shipRect.height / 2};

    //Flip shooting points around center of the ship
    for(sf::Vector2f &shootingPoint : shootingPoints){
        shootingPoint = Helpers::flipPointVertically(shootingPoint, shipCenter);
    }
}


void Player_Ship::setScale(float scale_x, float scale_y){
    Animation::setScale(scale_x, scale_y);

    //In addition to the setScale provided by Animation,
    //scale shooting points as well

    for(sf::Vector2f &shootingPoint : shootingPoints){
        shootingPoint.x *= scale_x;
        shootingPoint.y *= scale_y;
    }
}


bool Player_Ship::isHitBy(sf::Sprite &collisionObj){
    bool hit = false;

    if(getRect().intersects(collisionObj.getGlobalBounds())){
        hit = Collision::PixelPerfectTest(frames[0], collisionObj);
    }

    return hit;
}


void Player_Ship::AI_MoveWithinBounds(int max_x, float speed){
    sf::FloatRect shipRect = getRect();

    //If no destination, find one
    if(destination == -1){
        destination = rand() % (int)(max_x - shipRect.width);
        destGreaterThanX = destination >= shipRect.left;
    }

    //Move left or right based on the destination
    if(destGreaterThanX)
        move(speed, 0);

    else move(-speed, 0);

    //Check if we have reached or surpassed the destination
    //If so, reset it
    if(destGreaterThanX != (destination >= shipRect.left))
        destination = -1;
}


//Adds a point on the ship to shoot from
void Player_Ship::addShootingPoint(float x, float y){
    sf::Vector2f shipScale = getScale();
    sf::Vector2f point;

    //Scale the point to match the ship's scale before adding it
    point.x = x * shipScale.x;
    point.y = y * shipScale.y;
    shootingPoints.push_back(point);
}



void Player_Ship::setMsBetweenShots(int ms){
    msBetweenShots = ms;
}

ShipTypes Player_Ship::getShipType(){
    return shipType;
}


void Player_Ship::setBulletScale(float scale_x, float scale_y){
    bulletSprite.setScale(scale_x, scale_y);
}


void Player_Ship::initMosquito(){

    //Adding shooting points inside the original texture
    addShootingPoint(310, 0);

    setMsBetweenFrames(60);
    setMsBetweenShots(100);
    dmg = 2;

    setScale(0.10 * scaleMultiplier, 0.10 * scaleMultiplier);
    setBulletScale(0.3 * scaleMultiplier, 0.35 * scaleMultiplier);
    shipType = ShipTypes::mosquito;
    health = 15;
}


void Player_Ship::initDragon(){
    addShootingPoint(190, 200);
    addShootingPoint(253, 125);
    addShootingPoint(314, 202);

    setMsBetweenFrames(30);
    setMsBetweenShots(70);
    dmg = 1;

    setScale(0.18 * scaleMultiplier, 0.18 * scaleMultiplier);
    setBulletScale(0.4 * scaleMultiplier, 0.6 * scaleMultiplier);
    shipType = ShipTypes::dragon;
    health = 30;
}


void Player_Ship::initEagle(){
    setMsBetweenFrames(40);
    setMsBetweenShots(80);
    dmg = 1;

    //Adding shooting points inside the original texture
    addShootingPoint(70, 200);
    addShootingPoint(380, 200);

    setScale(0.14 * scaleMultiplier, 0.14 * scaleMultiplier);
    setBulletScale(0.45 * scaleMultiplier, 0.45 * scaleMultiplier);
    shipType = ShipTypes::eagle;
    health = 20;
}