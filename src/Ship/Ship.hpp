#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject/GameObject.hpp"
#include "../NewAnimation/Animation.hpp"
#include "../NewAnimation/SpriteSheet.hpp"

class Ship : public GameObject{
    public:
    enum class Type{mosquito, eagle, dragon, none};
    enum class Team{blue, red, neutral};

    //Constructors
    Ship(const SpriteSheet& spriteSheet);

    //Destructors
    virtual ~Ship();

    //Setters
    void setType(Type newType);

    //Getters

    //Other
    virtual void update(float timeDelta);
    void draw(sf::RenderWindow& window);

    protected:
    Team team;
    Type type;
    NewAnimation shipAnimation;
};