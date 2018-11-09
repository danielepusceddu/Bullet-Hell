#include "Animation.hpp"


void Animation::toggleInvisibility(){
    sf::Color newColor;

    if(invisible)
        newColor = sf::Color{255, 255, 255, 255};

    else newColor = sf::Color{255, 255, 255, 0};

    for(auto frame : frames)   
        frame.setColor(newColor);

    invisible = !invisible;
}

bool Animation::isInvisible(){
    return invisible;
}


int Animation::drawAnimation(sf::RenderWindow &window){
    //If this is the first time we're drawing, reset clock
    //So we are sure to draw the first frame
    if(this->firstDraw){
        this->clock.restart();
        this->firstDraw = false;
    }

    //Select frame to draw based on time elapsed since clock restart and msBetweenFrames
    sf::Time elapsed = this->clock.getElapsedTime();
    int frame = (int)((elapsed.asMilliseconds() / ms_between_frames) % this->frames.size());

    //If flash method has been called
    if(this->flashMsDuration){
        //Draw a flashed frame if flashMsDuration hasn't passed since method call
        if(this->flashStart + this->flashMsDuration >= this->clock.getElapsedTime().asMilliseconds()){
            this->frames[frame].setColor(this->flashColor);
            window.draw(this->frames[frame]);
            this->frames[frame].setColor(sf::Color::White);
        }

        //Else zero flashMsDuration and draw normally
        else{
            this->flashMsDuration = 0; 
            window.draw(this->frames[frame]);
        }
    }

    //Else draw frame normally
    else window.draw(this->frames[frame]);

    //Return index of drawn frame
    return frame;
}


//Change animation's color for x ms
void Animation::flash(sf::Color flashColor, int flashMsDuration){
    this->flashColor = flashColor;
    this->flashMsDuration = flashMsDuration;
    this->flashStart = this->clock.getElapsedTime().asMilliseconds();
}


//Vertical flip
void Animation::flipVertically(){
    sf::Vector2u textureSize;

    for(sf::Sprite &frame : this->frames){
        auto scale = frame.getScale();
        auto bounds = frame.getGlobalBounds();
        frame.setScale(scale.x, -scale.y);
        frame.setOrigin(0, -bounds.height);
        frame.move(0, bounds.height);
        //Modifying the texture rect breaks Collision.h
        //frame.move(bounds.width, bounds.height);
        //textureSize = frame.getTexture()->getSize();
        //frame.setTextureRect(sf::IntRect{0, (int)textureSize.y, (int)textureSize.x, -(int)textureSize.y});
    }
}


//Movement
void Animation::move(float offset_x, float offset_y){
    //For each frame, move by offsets provided
    for(sf::Sprite &frame : this->frames)
        frame.move(offset_x, offset_y);
}

//Controlled Movement
void Animation::moveUp(float speed, int minY){
    sf::FloatRect shipRect = this->getRect();

    if(shipRect.top - speed >= minY)
        this->setPos(shipRect.left, shipRect.top - speed);
}


void Animation::moveDown(float speed, int maxY){
    sf::FloatRect shipRect = this->getRect();

    if(shipRect.top + shipRect.height + speed <= maxY)
        this->setPos(shipRect.left, shipRect.top + speed);
}


void Animation::moveLeft(float speed, int minX){
    sf::FloatRect shipRect = this->getRect();

    if(shipRect.left - speed >= minX)
        this->setPos(shipRect.left - speed, shipRect.top);
}


void Animation::moveRight(float speed, int maxX){
    sf::FloatRect shipRect = this->getRect();

    if(shipRect.left + shipRect.width + speed <= maxX)
        this->setPos(shipRect.left + speed, shipRect.top);
}


//Setters
void Animation::setMsBetweenFrames(int ms){
    this->ms_between_frames = ms;
}

void Animation::setScale(float scale_x, float scale_y){ //virtual
    for(sf::Sprite &frame : this->frames)
        frame.setScale(scale_x, scale_y);
}

void Animation::setPos(float x, float y){
    for(sf::Sprite &frame : this->frames)
        frame.setPosition(x, y);
}

//Getters
sf::Vector2f Animation::getScale(){
    return this->frames[0].getScale();
}

sf::Vector2f Animation::getPos(){
    return this->frames[0].getOrigin() + this->frames[0].getPosition();
}

sf::FloatRect Animation::getRect(){
    return this->frames[0].getGlobalBounds();
}