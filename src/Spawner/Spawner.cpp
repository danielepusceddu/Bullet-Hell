#include "Spawner.hpp"

Spawner::Spawner(Bus& bus, std::vector<sf::Sprite>& bullets):
BusListener{bus}, 
bulletVec{bullets},
randEng{static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())}
{
    redBullet.loadFromFile("../assets/textures/red/bullet.bmp");
    redMosquito.loadFromFile("../assets/textures/red/mosquito.png");
    redDragon.loadFromFile("../assets/textures/red/dragon.png");
    redEagle.loadFromFile("../assets/textures/red/eagle.png");
}


void Spawner::notify(Message msg){
    switch(msg.getType()){
        case Message::Type::SHIP_SHOT:{
            Ship* ship = dynamic_cast<Ship*>(&msg.getCreator());
            if(ship != NULL)
                spawnBullet(*ship);
        }
        break;

        default:
        break;
    }
}


void Spawner::spawnBullet(Ship& ship){
    sf::Vector2f shipScale = ship.getScale();
    sf::FloatRect shipRect = ship.getGlobalRect();
    sf::Vector2f bulletPos;
    sf::Vector2f bulletScale;
    sf::Texture& bulletText = redBullet;

    switch(ship.getType()){
        default:
        case Ship::Type::mosquito:{
            bulletVec.push_back(sf::Sprite{bulletText});

            bulletScale.x = shipScale.x * 2;
            bulletScale.y = shipScale.y * 2;
            bulletVec.back().setScale(bulletScale);

            sf::FloatRect bulletRect = bulletVec.back().getGlobalBounds();
            bulletPos.x = (shipRect.left + shipRect.width / 2) - (bulletRect.width / 2);
            if(shipScale.y >= 0)
                bulletPos.y = shipRect.top - bulletRect.height;

            else
                bulletPos.y = shipRect.top + shipRect.height + bulletRect.height;

            bulletVec.back().setPosition(bulletPos);
        }
        break;
    }
}


void Spawner::spawnAI(std::vector<AI_Ship>& enemyVec, sf::IntRect spawnBounds){
    std::uniform_int_distribution<int> posPicker{0, spawnBounds.width};

    //Choose the ship type
    Ship::Type shipType = shipPicker();
    sf::Texture& texture = texturePicker(shipType);

    //Create it
    enemyVec.push_back(AI_Ship{getBus(), SpriteSheet{texture, 512}});
    enemyVec.back().setType(shipType);

    //Flip it
    sf::Vector2f scale = enemyVec.back().getScale();
    enemyVec.back().setScale(sf::Vector2f{0.2, scale.y * -1.0f});
    enemyVec.back().move(sf::Vector2f{0, enemyVec.back().getGlobalRect().height});

    //Choose its spawn point
    spawnPosition(enemyVec.back(), spawnBounds);

    //Choose its team
    enemyVec.back().setTeam(Ship::Team::red);

    //Set shot cooldown
    enemyVec.back().setMinTimeBetweenShots(sf::milliseconds(300));

    //Set its space limits
    enemyVec.back().setBounds(sf::FloatRect{static_cast<float>(spawnBounds.left), 
                                            static_cast<float>(spawnBounds.top), 
                                            static_cast<float>(spawnBounds.width), 
                                            static_cast<float>(spawnBounds.height)});
}


void Spawner::spawnPosition(AI_Ship& ship, sf::IntRect spawnBounds){
    std::uniform_int_distribution<int> xPicker{0, spawnBounds.width};
    std::uniform_int_distribution<int> yMultiplier{0, 2};
    sf::Vector2f movement{static_cast<float>(xPicker(randEng)), yMultiplier(randEng) * ship.getGlobalRect().height};
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
        default:
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