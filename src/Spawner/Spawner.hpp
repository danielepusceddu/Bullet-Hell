#pragma once
#include "../Ship/AI_Ship.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <chrono>

class Spawner{
    public:
    Spawner();
    void spawnAI(std::vector<AI_Ship>& enemyVec, sf::IntRect spawnBounds);

    private:
    //Private Methods
    Ship::Type shipPicker();
    void spawnPosition(AI_Ship& ship, sf::IntRect spawnBounds);
    sf::Texture& texturePicker(Ship::Type shipType);

    //Random
    std::default_random_engine randEng;

    //Textures
    sf::Texture redEagle;
    sf::Texture redDragon;
    sf::Texture redMosquito;
};