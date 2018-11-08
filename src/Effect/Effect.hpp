#pragma once
#include "../Animation/Animation.hpp"


//Animation that plays once, starting from the first frame.
class Effect : public Animation{
    protected:
        sf::Int32 lastTimeDrawn = 0;
        bool playing = false;
        unsigned int currentFrame = 0;

    public:
        //Constructor using initializer list
        template<std::size_t SIZE> 
        Effect(std::array<sf::Texture, SIZE> &textures) : Animation(textures){}

        void play();
        bool isPlaying();
        void drawNext(sf::RenderWindow &window);
        virtual ~Effect(){}
};