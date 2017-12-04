#include "Obstacle.h"
#include "Utility.h"
#include "Math.h"

Obstacle::Obstacle(float minSize, float maxSize, sf::Vector2u windowSize)
{
	this->minSize = minSize;
	this->maxSize = maxSize;
	this->windowSize = windowSize;
	this->reset();
}

Obstacle::~Obstacle()
{
}

void Obstacle::reset()
{
	this->originalSize = Utility::getRandomNumber(this->minSize, this->maxSize);
	this->size = this->originalSize;
	this->health = (this->size / this->maxSize) * 100.f; // if the object is small it got less life
	this->color = sf::Color(Utility::getRandomNumber(0, 255), Utility::getRandomNumber(0, 255), Utility::getRandomNumber(0, 255), 255);
	this->angle = 0.f;
	this->rotationSpeed = Utility::getRandomNumber(-5.f, 5.f);
	this->speed = Utility::getRandomNumber(75.f, 150.f);
	

	int spawnPoint = Utility::getRandomNumber(1, 4);

	//Above game screen
	if (spawnPoint == 1)
	{
		this->position = Utility::getRandomVector(0.f, static_cast<float>(this->windowSize.x), -150.f, -100.f);
	}


	//Right side of screen
	if (spawnPoint == 2)
	{
		this->position = Utility::getRandomVector(static_cast<float>(this->windowSize.x) + 100.f, 
			static_cast<float>(this->windowSize.x) + 150.f, 
			0.f,
			static_cast<float>(this->windowSize.y));
	}


	//Below game screen
	if (spawnPoint == 3)
	{
		this->position = Utility::getRandomVector(0.f, 
			static_cast<float>(this->windowSize.x), 
			static_cast<float>(this->windowSize.y) + 100.f, 
			static_cast<float>(this->windowSize.y) + 150.f);
	}


	//Left side of screen
	if (spawnPoint == 4)
	{
		this->position = Utility::getRandomVector(-100.f,
			-150.f,
			0.f, 
			static_cast<float>(this->windowSize.y));
	}

	this->calculateDirection();

}

void Obstacle::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Obstacle::setHealth(float health)
{
	this->health = health;
}

void Obstacle::setSize(float size)
{
	this->size = size;
}

void Obstacle::updateViewport(sf::Vector2u windowSize)
{
	this->windowSize = windowSize;
}

void Obstacle::calculateDirection()
{
	sf::Vector2f randomDestinationPoint = Utility::getRandomVector(50.f, this->windowSize.x - 50.f, this->windowSize.y / 4.f, this->windowSize.y / 2.f);
	this->dirVec = CustomMath::getDifferenceNormalized(this->position, randomDestinationPoint);
}

sf::Vector2f Obstacle::getPosition() const
{
	return this->position;
}

sf::Color Obstacle::getColor() const
{
	return this->color;
}

sf::Vector2f Obstacle::getDirection() const
{
	return this->dirVec;
}

float Obstacle::getHealth() const
{
	return this->health;
}

float Obstacle::getCurrentSize() const
{
	return this->size;
}

float Obstacle::getOriginalSize() const
{
	return this->originalSize;
}
