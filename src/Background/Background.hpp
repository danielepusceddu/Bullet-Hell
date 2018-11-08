#pragma once

#include <SFML/Graphics.hpp>
#include <array>

//Animated background
class Background{
    private:
        int width;
        int height;
        std::array<sf::Sprite, 2> frames;

    public:
        Background(const sf::Texture &bg_texture, unsigned int screen_w, unsigned int screen_h);
        void moveDown(float offset);
        void draw(sf::RenderWindow &window);
};