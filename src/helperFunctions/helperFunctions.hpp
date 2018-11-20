#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

namespace Helpers{
    std::string minutesAndSeconds(sf::Time time);
    std::string allUpperCase(std::string str);
    sf::FloatRect scaleRect(sf::FloatRect rect, float scaleX, float scaleY);
    sf::Vector2f flipPointVertically(sf::Vector2f point, sf::Vector2f center);
    sf::FloatRect flipRectVertically(sf::FloatRect rect, sf::Vector2f center);

    //Load a sequence of textures
    template<std::size_t SIZE> 
    void loadTextures(std::array<sf::Texture, SIZE> &texts, std::string path){
        size_t textNum = path.find("$d");

        //If $d is missing, return
        if(textNum == std::string::npos){
            std::cout << "Missing $d\n"; //placeholder, I should throw an exception
            return;
        }

        //else for x in range(0, SIZE)
        //textures[x].load(path.replace("$d", x))
        for(unsigned int i = 0; i < SIZE; i++){
            std::ostringstream number;
            std::string pathCopy = path;
            number << i;
            texts[i].loadFromFile(pathCopy.replace(textNum, 2, number.str()));
        }
    }
}