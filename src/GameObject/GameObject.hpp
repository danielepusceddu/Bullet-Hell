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
	int getSpeed() const;
	sf::FloatRect getBounds() const;
	sf::FloatRect getGlobalRect() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getPos() const;

	//Movement
	void move(sf::Vector2f movement);
	void moveLeft(float timeDelta);
	void moveRight(float timeDelta);
	void moveUp(float timeDelta);
	void moveDown(float timeDelta);

	//Other
	virtual void draw(sf::RenderWindow& window);
	bool isHitBy(sf::Sprite other) const;

	protected:
	int speed = 1;
	sf::FloatRect bounds;
	sf::Sprite sprite;
};