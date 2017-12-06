#include "ProjectileHandler.h"
#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "Math.h"
#include "Utility.h"

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
					5,i);
				
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
	if (projectileDirection.x < 0.0f)
	{
		projectileDirection.x = Utility::getRandomNumber(10.f, 90.f);
	}
	else
	{
		projectileDirection.x = Utility::getRandomNumber(-90.f, -10.f);
	}

	if (projectileDirection.y < 0.0f)
	{
		projectileDirection.y = Utility::getRandomNumber(10.f, 90.f);
	}
	else
	{
		projectileDirection.y = Utility::getRandomNumber(-90.f, -10.f);
	}
	projectileDirection /= 90.f;

	for (int i = 0; i < nrOfParticless; i++)
	{
		this->particleHandler->addParticle(position, projectileDirection, color, Utility::getRandomNumber(4.f,7.f),0.3f);
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