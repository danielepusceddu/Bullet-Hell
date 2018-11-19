#pragma once
#include <SFML/Graphics.hpp>
#include "../Bus/BusWriter.hpp"
#include "../GameObject/GameObject.hpp"
#include "../NewAnimation/Animation.hpp"
#include "../NewAnimation/SpriteSheet.hpp"

class Ship : public GameObject, public BusWriter{
    public:
    enum class Type{mosquito, eagle, dragon, none};
    enum class Team{blue, red, neutral};

    //Constructors
    Ship(Bus& bus, const SpriteSheet& spriteSheet);

    //Destructors
    virtual ~Ship();

    //Setters
    void setMinTimeBetweenShots(sf::Time time);
    void setType(Type newType);
    void setTeam(Team newTeam);

    //Getters
    bool isReadyToShoot();
    Type getType();
    Team getTeam();

    //Other
    virtual void update(float timeDelta);
    bool shoot();
    void draw(sf::RenderWindow& window);

    protected:
    //Ship Information
    Team team;
    Type type;

    //Ship Animation
    NewAnimation shipAnimation;

    //Shot Timing
    sf::Clock clock;
    bool readyToShoot = true;
    sf::Time lastShot = sf::Time::Zero;
    sf::Time timeBetweenShots = sf::Time::Zero;
};