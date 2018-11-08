#include "PlayerShip.hpp"
#include "../../extlibs/Collision/Collision.h"

//****************
//*PUBLIC METHODS*
//****************

//Shoot method. Returns vector of bullets
std::vector<sf::Sprite> Player_Ship::shoot(){
    sf::Time elapsed = this->clock.getElapsedTime();
    std::vector<sf::Sprite> shots;

    //If enough time has passed
    if(elapsed.asMilliseconds() - this->lastShot >= this->msBetweenShots){
        sf::FloatRect bulletRect = this->bulletSprite.getGlobalBounds();
        sf::Vector2f shipPos = this->getPos();

        //Place a bullet on each shooting point
        for(sf::Vector2f shootingPoint : this->shootingPoints){
            this->bulletSprite.setPosition(shootingPoint.x - bulletRect.width / 2, shootingPoint.y - bulletRect.height);
            this->bulletSprite.move(shipPos);
            shots.push_back(this->bulletSprite);
        }

        //Update time of last shot
        this->lastShot = elapsed.asMilliseconds();
    }

    //Return vector of bullets
    return shots;
}


void Player_Ship::initShipType(ShipTypes type){
    switch(type){
        case ShipTypes::eagle:
        this->initEagle();
        break;

        case ShipTypes::mosquito:
        this->initMosquito();
        break;

        case ShipTypes::dragon:
        this->initDragon();
        break;
    }
}

void Player_Ship::flipVertically(){
    Animation::flipVertically();    //Do default Animation flip

    //Get center of the ship
    sf::FloatRect shipRect = this->getRect();
    sf::Vector2f shipCenter = {shipRect.width / 2, shipRect.height / 2};

    //Flip shooting points around center of the ship
    for(sf::Vector2f &shootingPoint : this->shootingPoints){
        shootingPoint = Helpers::flipPointVertically(shootingPoint, shipCenter);
    }
}


void Player_Ship::setScale(float scale_x, float scale_y){
    Animation::setScale(scale_x, scale_y);

    //In addition to the setScale provided by Animation,
    //scale shooting points as well

    for(sf::Vector2f &shootingPoint : this->shootingPoints){
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
    sf::FloatRect shipRect = this->getRect();

    //If no destination, find one
    if(destination == -1){
        destination = rand() % (int)(max_x - shipRect.width);
        destGreaterThanX = destination >= shipRect.left;
    }

    //Move left or right based on the destination
    if(destGreaterThanX)
        this->move(speed, 0);

    else this->move(-speed, 0);

    //Check if we have reached or surpassed the destination
    //If so, reset it
    if(destGreaterThanX != (destination >= shipRect.left))
        destination = -1;
}


//Adds a point on the ship to shoot from
void Player_Ship::addShootingPoint(float x, float y){
    sf::Vector2f shipScale = this->getScale();
    sf::Vector2f point;

    //Scale the point to match the ship's scale before adding it
    point.x = x * shipScale.x;
    point.y = y * shipScale.y;
    this->shootingPoints.push_back(point);
}



void Player_Ship::setMsBetweenShots(int ms){
    this->msBetweenShots = ms;
}

ShipTypes Player_Ship::getShipType(){
    return this->shipType;
}


void Player_Ship::setBulletScale(float scale_x, float scale_y){
    this->bulletSprite.setScale(scale_x, scale_y);
}


void Player_Ship::initMosquito(){

    //Adding shooting points inside the original texture
    this->addShootingPoint(310, 0);

    this->setMsBetweenFrames(60);
    this->setMsBetweenShots(100);
    this->damage = 2;

    this->setScale(0.10 * this->scaleMultiplier, 0.10 * this->scaleMultiplier);
    this->setBulletScale(0.3 * this->scaleMultiplier, 0.35 * this->scaleMultiplier);
    this->shipType = ShipTypes::mosquito;
}


void Player_Ship::initDragon(){
    this->addShootingPoint(190, 200);
    this->addShootingPoint(253, 125);
    this->addShootingPoint(314, 202);

    this->setMsBetweenFrames(30);
    this->setMsBetweenShots(70);
    this->damage = 1;

    this->setScale(0.18 * this->scaleMultiplier, 0.18 * this->scaleMultiplier);
    this->setBulletScale(0.4 * this->scaleMultiplier, 0.6 * this->scaleMultiplier);
    this->shipType = ShipTypes::dragon;
}


void Player_Ship::initEagle(){
    this->setMsBetweenFrames(40);
    this->setMsBetweenShots(80);
    this->damage = 1;

    //Adding shooting points inside the original texture
    this->addShootingPoint(70, 200);
    this->addShootingPoint(380, 200);

    this->setScale(0.14 * this->scaleMultiplier, 0.14 * this->scaleMultiplier);
    this->setBulletScale(0.45 * this->scaleMultiplier, 0.45 * this->scaleMultiplier);
    this->shipType = ShipTypes::eagle;
}