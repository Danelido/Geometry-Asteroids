#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>

class Obstacle
{
protected:
	sf::Vector2u windowSize;
	sf::Vector2f position;
	sf::Vector2f dirVec;
	sf::Color color;

	float speed;
	float size;
	float originalSize;
	float minSize;
	float maxSize;
	float health;
	float rotationSpeed;
	float angle;
	
	void calculateDirection();

public:
	Obstacle(float minSize, float maxSize, sf::Vector2u windowSize);
	virtual ~Obstacle();
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	void reset();

	void setPosition(sf::Vector2f position);
	void setHealth(float health);
	void setSize(float size);
	void updateViewport(sf::Vector2u windowSize);

	sf::Vector2f getPosition() const;
	sf::Color getColor() const;
	sf::Vector2f getDirection() const;
	float getHealth() const;
	float getCurrentSize() const;
	float getOriginalSize() const;

};

#endif
