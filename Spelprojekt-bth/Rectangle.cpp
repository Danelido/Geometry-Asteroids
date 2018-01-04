#include "Rectangle.h"
#include "ResourceManager.h"

Rectangle::Rectangle(float minSize, float maxSize, sf::Vector2u windowSize)
	: Obstacle(minSize,maxSize,windowSize)
{
	this->length = this->size;
	this->rectangleShape.setTexture(&ResourceManager::getTexture("Quad"));
	this->rectangleShape.setSize(sf::Vector2f(this->length, this->length));
	this->rectangleShape.setOrigin(this->length  / 2.f, this->length / 2.f);
	this->rectangleShape.setFillColor(this->color);
}

Rectangle::~Rectangle()
{
}

void Rectangle::update(float dt)
{
	if (this->length != this->size)
	{
		this->length = this->size;
		this->rectangleShape.setSize(sf::Vector2f(this->length, this->length));
		this->rectangleShape.setOrigin(this->length/2.f, this->length /2.f);
	}

	if (this->rectangleShape.getFillColor() != this->color)
	{
		this->rectangleShape.setFillColor(this->color);
	}

	this->angle += this->rotationSpeed;
	this->position += this->dirVec * this->speed * dt;
	this->rectangleShape.setRotation(this->angle);
	this->rectangleShape.setPosition(this->position);
}

void Rectangle::render(sf::RenderWindow * window)
{
	window->draw(this->rectangleShape);
}
