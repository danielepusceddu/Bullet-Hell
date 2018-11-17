#include "Spawner.hpp"

Spawner::Spawner():
randEng{static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())}
{
    redMosquito.loadFromFile("../assets/textures/red/mosquito.png");
    redDragon.loadFromFile("../assets/textures/red/dragon.png");
    redEagle.loadFromFile("../assets/textures/red/eagle.png");
}

void Spawner::spawnAI(std::vector<AI_Ship>& enemyVec, sf::IntRect spawnBounds){
    std::uniform_int_distribution<int> posPicker{0, spawnBounds.width};

    //Choose the ship type
    Ship::Type shipType = shipPicker();
    sf::Texture& texture = texturePicker(shipType);

    //Create it
    enemyVec.push_back(AI_Ship{SpriteSheet{texture, 512}});
    enemyVec.back().setType(shipType);

    //Flip it
    sf::Vector2f scale = enemyVec.back().getScale();
    enemyVec.back().setScale(sf::Vector2f{0.2, scale.y * -1.0});
    enemyVec.back().move(sf::Vector2f{0, enemyVec.back().getGlobalRect().height});

    //Choose its spawn point
    spawnPosition(enemyVec.back(), spawnBounds);

    //Set its space limits
    enemyVec.back().setBounds(sf::FloatRect{static_cast<float>(spawnBounds.left), 
                                            static_cast<float>(spawnBounds.top), 
                                            static_cast<float>(spawnBounds.width), 
                                            static_cast<float>(spawnBounds.height)});
}


void Spawner::spawnPosition(AI_Ship& ship, sf::IntRect spawnBounds){
    std::uniform_int_distribution<int> xPicker{0, spawnBounds.width};
    std::uniform_int_distribution<int> yMultiplier{0, 2};
    sf::Vector2f movement{xPicker(randEng), yMultiplier(randEng) * ship.getGlobalRect().height};
    ship.move(movement);
}


Ship::Type Spawner::shipPicker(){
    Ship::Type pick;
    std::uniform_int_distribution<int> shipPicker{0, 100};
    int rand = shipPicker(randEng);

    if(rand < 10)
        pick = Ship::Type::dragon;

    else if(rand < 40)
        pick = Ship::Type::eagle;

    else pick = Ship::Type::mosquito;

    return pick;
}


sf::Texture& Spawner::texturePicker(Ship::Type shipType){
    sf::Texture* txt;

    switch(shipType){
        case Ship::Type::mosquito:
        txt = &redMosquito;
        break;

        case Ship::Type::eagle:
        txt = &redEagle;
        break;

        case Ship::Type::dragon:
        txt = &redDragon;
        break;
    }

    return *txt;
}