#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "Player.h"
#include "Utility.h"
#include "Math.h"

#include <iostream>

ObstacleHandler::ObstacleHandler(Player* player, ParticleHandler* particleHandler, sf::Vector2u windowSize)
{
	this->player = player;
	this->particleHandler = particleHandler;
	this->windowSize = windowSize;
	this->maxObstacles = 30;
	this->nrOfObstacles = 0;
	this->nrOfObstaclesDestroyed = 0;
	this->initiateArray();
}

ObstacleHandler::~ObstacleHandler()
{
	this->freeMemory();
}

void ObstacleHandler::update(float dt)
{
	for (int i = 0; i < this->nrOfObstacles; i++)
	{
		this->obstacles[i]->update(dt);
		if(!this->collisionWithPlayer())
		{
			this->checkIfOutOfBounds(i);
		}
	}
}

void ObstacleHandler::render(sf::RenderWindow* window)
{
	for (int i = 0; i < this->nrOfObstacles; i++)
	{
		this->obstacles[i]->render(window);
	}
}

void ObstacleHandler::addCircleObstacle()
{
	if (this->nrOfObstacles < this->maxObstacles)
	{
		this->obstacles[this->nrOfObstacles++] = new Circle(40.f,80.f, this->windowSize);
		
	}
}

void ObstacleHandler::addRectangleObstacle()
{
	if (this->nrOfObstacles < this->maxObstacles)
	{
		this->obstacles[this->nrOfObstacles++] = new Rectangle(40.f, 80.f, this->windowSize);
		
	}
}

void ObstacleHandler::addTriangleObject()
{
	if (this->nrOfObstacles < this->maxObstacles)
	{
		this->obstacles[this->nrOfObstacles++] = new Triangle(40.f, 80.f, this->windowSize);
		
	}
}

bool ObstacleHandler::collisionWithPlayer()
{
	for (int i = 0; i < this->nrOfObstacles; i++)
	{	
		if (CustomMath::intersection(this->player->getPosition(), this->player->getSize(), this->obstacles[i]->getPosition(), this->obstacles[i]->getCurrentSize()))
		{
			this->player->setHealth(this->player->getHealth() - (this->obstacles[i]->getCurrentSize() * 0.10f));
			this->makeEffect(i);
			this->obstacles[i]->reset();
			return true;
		}
	}
	return false;
}

void ObstacleHandler::removeAllObstacles()
{
	for (int i = 0; i < this->nrOfObstacles; i++)
	{
		delete this->obstacles[i];
	}
	this->nrOfObstacles = 0;
}

int ObstacleHandler::getNrOfObstacles() const
{
	return this->nrOfObstacles;
}

int ObstacleHandler::getNrOfDestroyedObstacles() const
{
	return this->nrOfObstaclesDestroyed;
}

Obstacle ** ObstacleHandler::getArray() const
{
	return this->obstacles;
}

void ObstacleHandler::updateViewport(sf::Vector2u windowSize)
{
	this->windowSize = windowSize;
	
	for (int i = 0; i < this->nrOfObstacles; i++)
	{
		this->obstacles[i]->updateViewport(this->windowSize);
	}
}

void ObstacleHandler::decreaseLife(int index)
{
	float damageDone = Utility::getRandomNumber(8.f, 16.f);
	this->obstacles[index]->setHealth(this->obstacles[index]->getHealth() - damageDone );
	this->obstacles[index]->setSize(this->obstacles[index]->getCurrentSize() -  ((damageDone/10.f) * (this->obstacles[index]->getCurrentSize() * 0.025f)) );
	
	if (this->obstacles[index]->getHealth() <= 0.0f)
	{
		this->makeEffect(index);
		this->obstacles[index]->reset();
		this->nrOfObstaclesDestroyed++;
		this->player->incrementScore(15.f);
	}
	
}

void ObstacleHandler::checkIfOutOfBounds(int index)
{
	// these variables is created because it makes the if-statements easier to read
	sf::Vector2f tempPos = this->obstacles[index]->getPosition();
	sf::Vector2f direction = this->obstacles[index]->getDirection();
	float tempRadius = this->obstacles[index]->getCurrentSize();

	// Depending on which direction the obstacles are going
	
	// Going down and right
	if (direction.x > 0.f && direction.y > 0.f)
	{
		if (tempPos.x + tempRadius > static_cast<float>(this->windowSize.x) + 100|| tempPos.y - tempRadius > static_cast<float>(this->windowSize.y) + 100)
		{
			this->obstacles[index]->reset();
		}
	}

	// Going up and left
	if (direction.x < 0.f && direction.y < 0.f)
	{
		if (tempPos.x + tempRadius < 0.f - 100 || tempPos.y + tempRadius < 0.f - 100)
		{
			this->obstacles[index]->reset();
		}
	}

	// Going up and right
	if (direction.x > 0.f && direction.y < 0.f)
	{
		if (tempPos.x + tempRadius > static_cast<float>(this->windowSize.x) + 100 || tempPos.y + tempRadius < 0.f - 100)
		{
			this->obstacles[index]->reset();
		}
	}

	// Going down and left
	if (direction.x < 0.f && direction.y > 0.f)
	{
		if (tempPos.x + tempRadius > 0.f - 100 || tempPos.y - tempRadius > static_cast<float>(this->windowSize.y) + 100)
		{
			this->obstacles[index]->reset();
		}
	}
}

void ObstacleHandler::makeEffect(int index)
{
	
	for (int j = 0; j < 100; j++)
	{
		this->particleHandler->spawnParticleWithRandomDirection(this->obstacles[index]->getPosition(), this->obstacles[index]->getColor(),
			Utility::getRandomNumber(3.f, 10.f), 1.5f);
	}
}

void ObstacleHandler::freeMemory()
{
	for (int i = 0; i < this->nrOfObstacles; i++)
	{
		delete this->obstacles[i];
	}
	delete[] this->obstacles;
}

void ObstacleHandler::initiateArray()
{
	this->obstacles = new Obstacle*[this->maxObstacles];

	for (int i = 0; i < this->maxObstacles; i++)
	{
		this->obstacles[i] = nullptr;
	}
}
