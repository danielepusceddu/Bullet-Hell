#pragma once

#include <vector>
#include <functional>
#include "../Bus/Message.hpp"
#include "../Bus/BusWriter.hpp"
#include "../helperFunctions/helperFunctions.hpp"
#include "../Animation/Animation.hpp"

enum class ShipTypes{mosquito, eagle, dragon};

class Player_Ship : public Animation, public BusWriter{
    public:
        enum class Team{blue, red};
        int dmg = 1;
        void damage(int dmg);
        bool isDead(){return dead;}
        void setHealth(int health);
        int getHealth();

        //Constructor with ship type
        template<std::size_t SIZE>
        Player_Ship(Bus& pBus, ShipTypes type, Team team, float scaleMultiplier, const std::array<sf::Texture, SIZE> &ship_textures, const sf::Texture &bullet_texture);


        template<std::size_t SIZE>
        void switchShipType(ShipTypes type, std::array<sf::Texture, SIZE> &textures);

        //Bullet Stuff
        void setBulletScale(float scale_x, float scale_y);
        void addShootingPoint(float x, float y);
        void setMsBetweenShots(int ms);
        std::vector<sf::Sprite> shoot();
        ShipTypes getShipType();
        
        
        void AI_MoveWithinBounds(int max_x, float speed);

        bool isHitBy(sf::Sprite &collisionObj);
        
        void flipVertically() override;
        void setScale(float scale_x, float scale_y) override;
        virtual ~Player_Ship(){}


        private:
        Team _team;
        float scaleMultiplier = 1;
        ShipTypes shipType;
        int destination = -1;
        bool destGreaterThanX;

        sf::Sprite bulletSprite;
        sf::Int32 lastShot = -1000;
        int msBetweenShots = 1;
        std::vector<sf::Vector2f> shootingPoints;

        void initMosquito();
        void initEagle();
        void initDragon();
        void initShipType(ShipTypes type);
        bool dead = false;
        int health = 20;
};



//Constructor with ship type
template<std::size_t SIZE>
Player_Ship::Player_Ship(Bus& pBus, ShipTypes type, Team team, float scaleMultiplier, const std::array<sf::Texture, SIZE> &ship_textures, 
                         const sf::Texture &bullet_texture)
: Animation{ship_textures}, BusWriter{pBus}, _team{team}{

    //Animation Constructor + setting bullet textures
    bulletSprite.setTexture(bullet_texture);

    //Setting scaleMultiplier
    this->scaleMultiplier = scaleMultiplier;

    //Setting shooting points based on ship type
    this->initShipType(type);
}


//Switch the ship type
template<std::size_t SIZE>
void Player_Ship::switchShipType(ShipTypes type, std::array<sf::Texture, SIZE> &textures){
    //Do nothing if we're already the requested ship type
    if(this->shipType == type)
        return;

    //Else get current ship center
    sf::FloatRect oldShipRect = this->getRect();
    sf::Vector2f oldCenter{oldShipRect.left + oldShipRect.width / 2, oldShipRect.top + oldShipRect.height / 2};

    //Replace textures
    this->switchTextures(textures);

    //Clear shooting points
    this->shootingPoints.clear();

    //Add shooting points for new ship type
    this->initShipType(type);

    //Get new ship center
    sf::FloatRect newShipRect = this->getRect();
    sf::Vector2f newCenter{newShipRect.left + newShipRect.width / 2, newShipRect.top + newShipRect.height / 2};

    //Move so we're centered on the old center
    this->setPos(newShipRect.left + (oldCenter.x - newCenter.x), newShipRect.top + (oldCenter.y - newCenter.y));
}