#include "Circle.h"
#include "ResourceManager.h"

Circle::Circle(float minDiameter, float maxDiameter, sf::Vector2u windowSize) :
	Obstacle(minDiameter, maxDiameter, windowSize)
{
	this->radius = this->size / 2.f;
	this->circleShape.setTexture(&ResourceManager::getTexture("Circle"));
	this->circleShape.setRadius(this->radius);
	this->circleShape.setOrigin(this->radius, this->radius);
	this->circleShape.setFillColor(this->color);
}

Circle::~Circle()
{
}

void Circle::update(float dt)
{
	if (this->radius != this->size/2.f)
	{
		this->radius = this->size / 2.f;
		this->circleShape.setRadius(this->radius);
		this->circleShape.setOrigin(this->radius, this->radius);
	}

	if (this->circleShape.getFillColor() != this->color)
	{
		this->circleShape.setFillColor(this->color);
	}

	this->angle += this->rotationSpeed;
	this->position += this->dirVec * this->speed * dt;
	this->circleShape.setPosition(this->position);
	this->circleShape.setRotation(this->angle);
}

void Circle::render(sf::RenderWindow* window)
{
	window->draw(this->circleShape);
}
