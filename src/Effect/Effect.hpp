#pragma once
#include "../NewAnimation/SpriteSheet.hpp"
#include "../GameObject/GameObject.hpp"
#include "../NewAnimation/Animation.hpp"

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
    NewAnimation animation;
};
