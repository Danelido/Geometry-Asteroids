#ifndef CIRCLE_H
#define CIRCLE_H
#include "Obstacle.h"
#include <SFML/Graphics/CircleShape.hpp>

class Circle : public Obstacle
{

private:
	sf::CircleShape circleShape;
	float radius;

public:
	Circle(float minRadius, float maxRadius, sf::Vector2u windowSize);
	~Circle();

	void update(float dt) override;
	void render(sf::RenderWindow* window) override;

};

#endif
