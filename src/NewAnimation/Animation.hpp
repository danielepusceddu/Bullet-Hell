#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <vector>

class NewAnimation{
    public:
    //Constructor
    NewAnimation(sf::Sprite& sprite, unsigned int frameWidth);

    //Setters
    void setTimeBetweenFrames(sf::Time time);

    //Getters
    const sf::Sprite& getSprite();
    const sf::IntRect& getFrame();

    //Modifiers
    void update(sf::Sprite& target);

    private:
    //Sprite to animate
    sf::Sprite* sprite;

    //Frames
    std::vector<sf::IntRect> frames;

    //Current Frame Index
    int currentFrame = 0;

    //Clock to keep track of time
    sf::Clock clock;

    //Time to wait before switching frame
    sf::Time timeBetweenFrames = sf::Time::Zero;

    //When we last switched frame
    sf::Time lastFrameSwitch;
};