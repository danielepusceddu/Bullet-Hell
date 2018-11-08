#include "Effect.hpp"

void Effect::play(){
    this->playing = true; 
    this->currentFrame = 0;
}

bool Effect::isPlaying(){
    return this->playing;
}

void Effect::drawNext(sf::RenderWindow &window){
    if(this->playing){
        //Get index of the frame drawn by drawAnimation
        this->currentFrame = this->drawAnimation(window);

        //Stop playing if it's the last frame
        if(this->currentFrame == this->frames.size() - 1)
            this->playing = false;
    }
}