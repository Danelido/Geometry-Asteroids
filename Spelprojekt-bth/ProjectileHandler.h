#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H
#include "Projectile.h"
#include <vector>

class ObstacleHandler;
class ParticleHandler;

class ProjectileHandler
{
private:
	sf::Vector2u windowSize;
	static const int MAX_PROJECTILES = 100;
	int nrOfActiveProjectiles;
	Projectile projectiles[MAX_PROJECTILES];
	ObstacleHandler* obstacleHandler; // Pointer to the obstacle handler
	ParticleHandler* particleHandler;

	void swap(Projectile& e1, Projectile& e2);
	void checkIfOutOfBounds(int index);
	void removeProjectile(int index);
	bool collisionWithObstacles(int index);
	void generateEffect(sf::Vector2f position, sf::Vector2f projectileDirection, sf::Color color, int nrOfParticles, int obstacleIndex);
public:
	ProjectileHandler(ObstacleHandler* obstacleHandler,ParticleHandler* particleHandler ,sf::Vector2u windowSize);
	~ProjectileHandler();

	void update(float dt);
	void render(sf::RenderWindow* window);
	
	void addProjectile(sf::Vector2f position, sf::Vector2f dirVec);
	void removeAllProjectiles();
	
	int getNrOfProjectiles() const;
	void updateViewport(sf::Vector2u windowSize);

};


#endif
