#pragma once
#include <SFML/Graphics.hpp>

class GameObject{
	public:
	//Constructor
	GameObject(const sf::Texture& texture);

	//Destructor
	virtual ~GameObject();

	//Update
	virtual void update(float timeDelta) = 0;

	//Setters
	void setPos(sf::Vector2f newPos);
	void setSpeed(int newSpeed);
	void setBounds(sf::FloatRect newBounds);
	void setScale(sf::Vector2f scale);

	//Getters
	int getSpeed();
	sf::FloatRect getBounds();
	sf::FloatRect getGlobalRect();
	sf::Vector2f getScale();

	//Movement
	void move(sf::Vector2f movement);
	void moveLeft(float timeDelta);
	void moveRight(float timeDelta);
	void moveDown(float timeDelta);

	protected:
	int speed = 1;
	sf::FloatRect bounds;
	sf::Sprite sprite;
};