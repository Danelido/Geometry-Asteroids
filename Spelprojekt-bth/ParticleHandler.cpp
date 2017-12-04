#include "ParticleHandler.h"
#include "Utility.h"

ParticleHandler::ParticleHandler()
{
	this->nrOfActiveParticles = 0;
}

ParticleHandler::~ParticleHandler()
{
}

void ParticleHandler::update(float dt)
{
	for (int i = 0; i < this->nrOfActiveParticles; i++)
	{
		this->particles[i].update(dt);
		this->checkIfDead(i);
	}
}

void ParticleHandler::render(sf::RenderWindow * window)
{
	for (int i = 0; i < this->nrOfActiveParticles; i++)
	{
		this->particles[i].render(window);
	}
}

void ParticleHandler::addParticle(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime)
{
	if (this->nrOfActiveParticles < this->MAX_PARTICLES)
	{
		this->particles[this->nrOfActiveParticles++].activate(position, dirVec, color, speed, lifetime);
	}
}

void ParticleHandler::addParticleWithRandomDirection(sf::Vector2f position, sf::Color color, float speed, float lifetime)
{
	if (this->nrOfActiveParticles < this->MAX_PARTICLES)
	{

		this->particles[this->nrOfActiveParticles++].activate(position, (Utility::getRandomVector(-100.f,100.f) / 100.f), color, speed,lifetime);
	}
}

int ParticleHandler::getNrOfParticles() const
{
	return this->nrOfActiveParticles;
}

void ParticleHandler::checkIfDead(int index)
{
	if (!this->particles[index].isActive())
	{
		swap(particles[index], particles[--this->nrOfActiveParticles]);
	}
}
void ParticleHandler::swap(Particle& p1, Particle& p2)
{
	Particle temp = p1;
	p1 = p2;
	p2 = temp;
}
