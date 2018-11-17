#include "AIComponent.hpp"
#include <iostream>

//Constructor
AIComponent::AIComponent(){
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
    sf::FloatRect bounds = ship.getBounds();
    sf::FloatRect shipRect = ship.getGlobalRect();

    x_destination = rand() % (int)(bounds.width - shipRect.width - 1) + bounds.left;
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