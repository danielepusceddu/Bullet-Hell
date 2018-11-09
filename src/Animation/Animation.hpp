#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <array>

//Animation with loop
class Animation{
    protected:
        bool firstDraw = true;
        bool invisible = false;

        sf::Color flashColor = sf::Color::White;
        int flashMsDuration = 0;
        sf::Int32 flashStart = 0;

        int rotation = 0;
        sf::Clock clock;
        sf::Int32 ms_between_frames = 1;
        std::vector<sf::Sprite> frames;

    public:
        //Constructor
        template<std::size_t SIZE> 
        Animation(const std::array<sf::Texture, SIZE> &textures);

        //Setters
        virtual void setScale(float scale_x, float scale_y);
        void setPos(float x, float y);
        
        //Getters
        sf::Vector2f getScale();
        sf::Vector2f getPos();
        sf::FloatRect getRect();


        template<std::size_t SIZE> 
        void switchTextures(const std::array<sf::Texture, SIZE> &textures);

        int drawAnimation(sf::RenderWindow &window);

        void setMsBetweenFrames(int ms);

        void move(float offset_x, float offset_y);
        void moveUp(float speed, int minY);
        void moveDown(float speed, int maxY);
        void moveLeft(float speed, int minX);
        void moveRight(float speed, int maxX);

        virtual void flipVertically();
        void flash(sf::Color flashColor, int flashMsDuration);

        void toggleInvisibility();
        bool isInvisible();
};


//Constructor
template<std::size_t SIZE> 
Animation::Animation(const std::array<sf::Texture, SIZE> &textures){
    //Push each texture provided as an animation frame
    for(const sf::Texture &texture : textures){
        sf::Sprite temp;
        temp.setTexture(texture);
        this->frames.push_back(temp);
    }
}


template<std::size_t SIZE>
void Animation::switchTextures(const std::array<sf::Texture, SIZE> &textures){
    sf::Vector2f pos = this->getPos();
    this->frames.clear();   //Clear current sprites

    //Push each texture provided as an animation frame
    for(const sf::Texture &texture : textures){
        sf::Sprite temp;
        temp.setTexture(texture);
        temp.setPosition(pos);
        this->frames.push_back(temp);
    }
}