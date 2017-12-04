#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include "Particle.h"
class ParticleHandler
{
private:
	static const int MAX_PARTICLES = 200;
	int nrOfActiveParticles;
	Particle particles[MAX_PARTICLES];
	
	void checkIfDead(int index);
	void swap(Particle& p1, Particle& p2);

public:
	ParticleHandler();
	~ParticleHandler();

	void update(float dt);
	void render(sf::RenderWindow* window);
	void addParticle(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime);
	void addParticleWithRandomDirection(sf::Vector2f position, sf::Color color, float speed, float lifetime);

	int getNrOfParticles() const;
};


#endif
