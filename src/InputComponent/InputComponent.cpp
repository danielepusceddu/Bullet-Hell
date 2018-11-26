#include "InputComponent.hpp"
#include <iostream>

void InputComponent::update(Ship& ship, float timeDelta){
    if(shoot || shootToggle)
        ship.shoot();

    if(moveUp)
        ship.moveUp(timeDelta);

    if(moveDown)
        ship.moveDown(timeDelta);

    if(moveLeft)
        ship.moveLeft(timeDelta);

    if(moveRight)
        ship.moveRight(timeDelta);
}


void InputComponent::handleEvent(sf::Event event){
    bool modifier;

    switch(event.type){
        case sf::Event::KeyPressed:
        modifier = true;
        break;

        case sf::Event::KeyReleased:
        modifier = false;
        break;

        default:
        return;
        break;
    }

    switch(event.key.code){
        case sf::Keyboard::Space:
        shoot = modifier;
        break;

        case sf::Keyboard::G:
        shootToggle = !shootToggle;
        break;

        //Start Movement
        //Move Up
        case sf::Keyboard::W:
        case sf::Keyboard::I:
        case sf::Keyboard::Up:
        moveUp = modifier;
        break;

        //Move Down
        case sf::Keyboard::S:
        case sf::Keyboard::K:
        case sf::Keyboard::Down:
        moveDown = modifier;
        break;

        //Move Left
        case sf::Keyboard::A:
        case sf::Keyboard::J:
        case sf::Keyboard::Left:
        moveLeft = modifier;
        break;

        //Move Right
        case sf::Keyboard::D:
        case sf::Keyboard::L:
        case sf::Keyboard::Right:
        moveRight = modifier;
        break;

        default:
        break;
    }
}