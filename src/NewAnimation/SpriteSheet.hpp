#pragma once
#include <SFML/Graphics.hpp>

class SpriteSheet{
    public:
    SpriteSheet(const sf::Texture& text, unsigned int framewidth);
    const sf::Texture& texture;
    unsigned int frameWidth;
};