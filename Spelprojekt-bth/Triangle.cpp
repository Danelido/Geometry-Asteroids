#include "Triangle.h"
#include "ResourceManager.h"

Triangle::Triangle(float minRadius, float maxRadius, sf::Vector2u windowSize) :
	Obstacle(minRadius,maxRadius,windowSize)
{
	this->radius = this->size / 2.f;
	this->triangleShape.setTexture(&ResourceManager::getTexture("Triangle"));
	this->triangleShape.setRadius(this->radius);
	this->triangleShape.setOrigin(this->radius, this->radius);
	this->triangleShape.setPointCount(3);
	this->triangleShape.setFillColor(this->color);

}

Triangle::~Triangle()
{
}

void Triangle::update(float dt)
{
	if (this->radius != this->size / 2.f)
	{
		this->radius = this->size / 2.f;
		this->triangleShape.setRadius(this->radius);
		this->triangleShape.setOrigin(this->radius, this->radius);
	}

	if (this->triangleShape.getFillColor() != this->color)
	{
		this->triangleShape.setFillColor(this->color);
	}
	this->angle += this->rotationSpeed;
	this->position += this->dirVec * this->speed * dt;
	this->triangleShape.setRotation(this->angle);
	this->triangleShape.setPosition(this->position);
}

void Triangle::render(sf::RenderWindow * window)
{
	window->draw(this->triangleShape);
}
