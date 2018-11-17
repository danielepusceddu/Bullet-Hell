#include "GameObject.hpp"
#include <iostream>

//Constructor
GameObject::GameObject(const sf::Texture& texture):
sprite{texture}
{
}

GameObject::~GameObject() = default;


//Setters
void GameObject::setPos(sf::Vector2f newPos){
	sprite.setPosition(newPos);
}

void GameObject::setSpeed(int newSpeed){
	speed = newSpeed;
}

void GameObject::setBounds(sf::FloatRect newBounds){
	bounds = newBounds;
}

void GameObject::setScale(sf::Vector2f scale){
	sprite.setScale(scale);
}


//Getters

int GameObject::getSpeed(){
	return speed;
}

sf::FloatRect GameObject::getBounds(){
	return bounds;
}

sf::FloatRect GameObject::getGlobalRect(){
	return sprite.getGlobalBounds();
}

sf::Vector2f GameObject::getScale(){
	return sprite.getScale();
}


//Movement
void GameObject::move(sf::Vector2f movement){
	sprite.move(movement);
}

void GameObject::moveLeft(float timeDelta){
	sf::Vector2f currentPos{sprite.getPosition()};
	sf::Vector2f movement{-(speed * timeDelta), 0};
	sf::Vector2f newPos{currentPos + movement};

	if(bounds.contains(newPos))
		sprite.move(movement);
}

void GameObject::moveRight(float timeDelta){
	sf::Vector2f currentPos{sprite.getPosition()};
	sf::Vector2f movement{speed * timeDelta, 0};
	sf::Vector2f newPos{currentPos + movement};
	sf::FloatRect rect{getGlobalRect()};

	if(bounds.contains(newPos) && bounds.contains(newPos + sf::Vector2f{rect.width, 0}))
		sprite.move(movement);
}

void GameObject::moveDown(float timeDelta){
	sf::Vector2f currentPos{sprite.getPosition()};
	sf::Vector2f movement{0, speed * timeDelta};
	sf::Vector2f newPos{currentPos + movement};
	sf::FloatRect rect{getGlobalRect()};

	if(bounds.contains(newPos) && bounds.contains(newPos + sf::Vector2f{0, rect.height}))
		sprite.move(movement);
}