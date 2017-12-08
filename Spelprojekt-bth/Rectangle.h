#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Obstacle.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Rectangle : public Obstacle
{
private:
	sf::RectangleShape rectangleShape;
	float length;

public:
	Rectangle(float minSize, float maxSize, sf::Vector2u windowSize, bool dummy = false);
	~Rectangle();

	void update(float dt) override;
	void render(sf::RenderWindow* window) override;

};


#endif
