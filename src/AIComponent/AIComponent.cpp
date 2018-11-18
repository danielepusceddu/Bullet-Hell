#include "AIComponent.hpp"
#include <random>
#include <chrono>

//Constructor
AIComponent::AIComponent():
randEng{static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())}
{
    x_destination = -1;
}

//Update Method
void AIComponent::update(Ship& ship, float delta){

    if(x_destination == -1)
        getNewDestination(ship);

    else moveShip(ship, delta);

    if(reachedDestination(ship))
        x_destination = -1;
}

void AIComponent::getNewDestination(Ship& ship){
    //Calculating min x and max x
    sf::FloatRect bounds = ship.getBounds();
    sf::FloatRect shipRect = ship.getGlobalRect();
    int minX = static_cast<int>(bounds.left);
    int maxX = static_cast<int>(bounds.width - shipRect.width - 1);

    //Getting random x
    std::uniform_int_distribution<int> xPicker{minX, maxX};
    x_destination = xPicker(randEng);
    destGreaterThanX = x_destination >= shipRect.left;
}

void AIComponent::moveShip(Ship& ship, float delta){
    if(destGreaterThanX)
        ship.moveRight(delta);

    else ship.moveLeft(delta);
}

bool AIComponent::reachedDestination(Ship& ship){
    sf::FloatRect shipRect = ship.getGlobalRect();

    return destGreaterThanX != (x_destination >= shipRect.left);
}