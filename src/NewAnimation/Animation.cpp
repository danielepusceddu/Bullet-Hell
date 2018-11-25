#include "Animation.hpp"
#include <iostream>

NewAnimation::NewAnimation(sf::Sprite& targetSprite, unsigned int frameWidth): 
sprite{&targetSprite}
{
    lastFrameSwitch = clock.getElapsedTime();
    sf::Vector2u sheetSize = sprite->getTexture()->getSize();

    for(unsigned int i = 0; i < sheetSize.x; i += frameWidth)
        frames.push_back(sf::IntRect{(int)i, 0, (int)frameWidth, (int)sheetSize.y});
        
    sprite->setTextureRect(frames[0]);
}


void NewAnimation::update(sf::Sprite& target){
    sf::Time now = clock.getElapsedTime();

    //If enough time has passed, update current frame
    if(now - timeBetweenFrames >= lastFrameSwitch){
        currentFrame = ((long unsigned int)currentFrame < frames.size() - 1) ? currentFrame + 1 : 0;
        target.setTextureRect(frames[currentFrame]);
        lastFrameSwitch = now;
    }
}

int NewAnimation::getFrameIndex(){
    return currentFrame;
}

void NewAnimation::setTimeBetweenFrames(sf::Time time){
    timeBetweenFrames = time;
}


const sf::Sprite& NewAnimation::getSprite(){
    return *sprite;
}


const sf::IntRect& NewAnimation::getFrame(){
    return frames[currentFrame];
}