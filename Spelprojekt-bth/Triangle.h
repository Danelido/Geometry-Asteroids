#ifndef TRIANGLE_H
#define TRIANGLE_h
#include "Obstacle.h"
#include <SFML/Graphics/CircleShape.hpp>

class Triangle : public Obstacle
{

private:
	sf::CircleShape triangleShape;
	float radius;

public:
	Triangle(float minDiameter, float maxDiameter, sf::Vector2u windowSize);
	~Triangle();

	void update(float dt) override;
	void render(sf::RenderWindow* window) override;
};


#endif
