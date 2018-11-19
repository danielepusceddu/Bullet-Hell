#pragma once
#include "../Ship/AI_Ship.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <chrono>

class Spawner : public BusListener{
    public:
    Spawner(Bus &bus, std::vector<sf::Sprite>& bullets);
    void notify(Message msg) override;
    void spawnAI(std::vector<AI_Ship>& enemyVec, sf::IntRect spawnBounds);

    private:
    //Private Methods
    Ship::Type shipPicker();
    void spawnBullet(Ship& ship);
    void spawnPosition(AI_Ship& ship, sf::IntRect spawnBounds);
    sf::Texture& texturePicker(Ship::Type shipType);

    //Container references
    std::vector<sf::Sprite>& bulletVec;

    //Random
    std::default_random_engine randEng;

    //Textures
    sf::Texture redBullet;
    sf::Texture redEagle;
    sf::Texture redDragon;
    sf::Texture redMosquito;
};