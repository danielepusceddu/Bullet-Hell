#pragma once
#include "../Ship/AI_Ship.hpp"
#include "../Effect/Effect.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <chrono>

class Spawner : public BusListener{
    public:
    Spawner(Bus &bus, std::vector<sf::Sprite>& bullets, std::vector<Effect>& effects);
    void notify(Message msg) override;
    void spawnAI(std::vector<AI_Ship>& enemyVec, sf::IntRect spawnBounds);

    private:
    //Private Methods
    void spawnExplosion(const Ship& ship);
    Ship::Type shipPicker();
    void spawnBullet(Ship& ship);
    void spawnPosition(AI_Ship& ship, sf::IntRect spawnBounds);
    sf::Texture& texturePicker(Ship::Type shipType);

    //Container references
    std::vector<sf::Sprite>& bulletVec;
    std::vector<Effect>& effects;

    //Random
    std::default_random_engine randEng;

    //Textures
    sf::Texture blueExplosion;
    sf::Texture redExplosion;
    sf::Texture redBullet;
    sf::Texture redEagle;
    sf::Texture redDragon;
    sf::Texture redMosquito;
};