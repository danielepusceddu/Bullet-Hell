#include "Background.hpp"

//****************
//*PUBLIC METHODS*
//****************

//Constructor
Background::Background(const sf::Texture &bg_texture, unsigned int screen_w, unsigned int screen_h){
    sf::Vector2u texture_size = bg_texture.getSize();
    sf::Vector2f factors;

    this->width = screen_w;
    this->height = screen_h;

    //Factors to scale the sprite so it is the same size as the screen
    factors.x = (float)screen_w / texture_size.x;
    factors.y = (float)screen_h / texture_size.y;

    //Make 2 sprites from the background texture
    for(sf::Sprite &frame : frames){
        frame.setTexture(bg_texture);
        frame.setScale(factors);
    }

    //Set one of them to be just above the window
    frames.at(1).setPosition(0, 0 - this->height);
}


void Background::moveDown(float offset){
    sf::Vector2f position;

    //Move both sprites down
    for(sf::Sprite &frame : this->frames){
        frame.move(0, offset);
        position = frame.getPosition();

        //If one of the sprites goes under the window
        //Place it above the window so we can keep moving it down
        if(position.y > this->height)
            frame.setPosition(0, 0 - this->height);
    }
}


void Background::draw(sf::RenderWindow &window){
    for(sf::Sprite frame : this->frames)
        window.draw(frame);
}