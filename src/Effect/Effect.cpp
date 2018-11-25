#include "Effect.hpp"

//Constructor
Effect::Effect(const SpriteSheet& sheet):
GameObject{sheet.texture}, animation{sprite, sheet.frameWidth}
{

}

//Update
void Effect::update(float timeDelta){
    if(!finished){
        animation.update(sprite);

        if(animation.getFrameIndex() > 0)
            firstFrame = false;

        else if(!firstFrame)
            finished = true;
    }
}

void Effect::draw(sf::RenderWindow& window){
    if(!finished)
        window.draw(sprite);
}

void Effect::setTimeBetweenFrames(sf::Time time){
    animation.setTimeBetweenFrames(time);
}

bool Effect::isFinished() const{
    return finished;
}