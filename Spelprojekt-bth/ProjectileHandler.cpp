#include "ProjectileHandler.h"
#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "Math.h"
#include "Utility.h"
#include <iostream>


ProjectileHandler::ProjectileHandler(ObstacleHandler* obstacleHandler, ParticleHandler* particleHandler, sf::Vector2u windowSize)
{
	this->obstacleHandler = obstacleHandler;
	this->particleHandler = particleHandler;
	this->windowSize = windowSize;
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::update(float dt)
{
		for (int i = 0; i < this->nrOfActiveProjectiles; i++)
		{
			this->projectiles[i].update(dt);
			if (!this->collisionWithObstacles(i))
			{
				this->checkIfOutOfBounds(i);
			}
		}
}

void ProjectileHandler::render(sf::RenderWindow* window)
{
	for (int i = 0; i < this->nrOfActiveProjectiles; i++)
	{
		this->projectiles[i].render(window);
	}
}

void ProjectileHandler::addProjectile(sf::Vector2f position, sf::Vector2f dirVec)
{
	if (this->nrOfActiveProjectiles < this->MAX_PROJECTILES)
	{
		this->projectiles[this->nrOfActiveProjectiles++].activate(position, dirVec);
	}
}

void ProjectileHandler::removeProjectile(int index)
{
	this->projectiles[index].deActivate();
	// To keep every deactivated projectile in the back of the array
	// because it saves time when adding a new projectile because then you dont
	// need too loop through the array to get a deactivated projectile
	this->swap(this->projectiles[index], this->projectiles[this->nrOfActiveProjectiles-1]);
	this->nrOfActiveProjectiles--;
}

void ProjectileHandler::removeAllProjectiles()
{
	for (int i = 0; i < this->nrOfActiveProjectiles; i++)
	{
		this->projectiles[i].deActivate();
	}
}

bool ProjectileHandler::collisionWithObstacles(int index)
{
	sf::Vector2f projectilePosition = this->projectiles[index].getPosition();
	float projectileSize = this->projectiles[index].getSize();

	for (int i = 0; i < obstacleHandler->getNrOfObstacles(); i++)
	{
		if (CustomMath::intersection(projectilePosition,projectileSize,
			this->obstacleHandler->getArray()[i]->getPosition(), this->obstacleHandler->getArray()[i]->getCurrentSize()))
		{
			
				this->generateEffect(projectilePosition, 
					this->projectiles[index].getDirection(),
					this->obstacleHandler->getArray()[i]->getColor(),
					25,i);
				
			this->removeProjectile(index);
			this->obstacleHandler->decreaseLife(i);
			return true;
		}
	}
	return false;
}

void ProjectileHandler::checkIfOutOfBounds(int index)
{
	sf::Vector2f tempPos = this->projectiles[index].getPosition();
	float tempSize = this->projectiles[index].getSize();
	
	if (tempPos.x + tempSize  > static_cast<float>(this->windowSize.x) || tempPos.x - tempSize < 0
		|| tempPos.y + tempSize  > static_cast<float>(this->windowSize.y) || tempPos.y - tempSize < 0)
	{
		removeProjectile(index);
	}
}

void ProjectileHandler::generateEffect(sf::Vector2f position, sf::Vector2f projectileDirection, sf::Color color, int nrOfParticless, int obstacleIndex)
{
	//// Todo: fix more accurate spread
	float RangeforX = ((1.f - abs(projectileDirection.x)) * 100.f) / 2.f;
	float RangeforY = ((1.f - abs(projectileDirection.y)) * 100.f) / 2.f;
	
	//Reverse it
	projectileDirection *= -1.f;

	for (int i = 0; i < nrOfParticless; i++)
	{
		//Randomize x & y-direction within the range limit
		float spreadX = Utility::getRandomNumber(-RangeforX, RangeforX);
		float spreadY = Utility::getRandomNumber(-RangeforY, RangeforY);
		//Normalize it
		spreadX /= 100.f;
		spreadY /= 100.f;
		//Add it
		projectileDirection += sf::Vector2f(spreadX, spreadY);
		//Spawn a particle
		this->particleHandler->spawnParticle(position, projectileDirection, color, Utility::getRandomNumber(1.f,4.f),0.60f);
	}
}

int ProjectileHandler::getNrOfProjectiles() const
{
	return this->nrOfActiveProjectiles;
}

void ProjectileHandler::updateViewport(sf::Vector2u windowSize)
{
	this->windowSize = windowSize;
}

void ProjectileHandler::swap(Projectile& e1, Projectile& e2)
{
	Projectile temp = e1;
	e1 = e2;
	e2 = temp;
}