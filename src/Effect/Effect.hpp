#pragma once
#include "../Animation/SpriteSheet.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Animation/Animation.hpp"

class Effect : public GameObject{
    public:
    //Constructor
    Effect(const SpriteSheet& sheet);

    //Setters
    void setTimeBetweenFrames(sf::Time time);

    //Getters
    bool isFinished() const;

    //Other
    void draw(sf::RenderWindow& window) override;
    void update(float timeDelta) override;

    private:
    bool finished = false;
    bool firstFrame = true;
    Animation animation;
};
