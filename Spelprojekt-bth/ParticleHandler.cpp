#include "ParticleHandler.h"
#include "Utility.h"

ParticleHandler::ParticleHandler() 
{
	this->nrOfActiveParticles = 0;
	this->vertices.setPrimitiveType(sf::Points);
	this->vertices.resize(this->MAX_PARTICLES);
	this->debug = false;
	
	if (this->debug)
	{
		info.setPosition(sf::Vector2f(300, 10));
	}
}

ParticleHandler::~ParticleHandler()
{
}

void ParticleHandler::update(float dt)
{
	for (int i = 0; i < this->nrOfActiveParticles; i++)
	{
		Particle& p = this->particles[i];
		
		p.lifetime -= dt;

		if (p.lifetime <= 0.0f)
		{
			this->vertices[i].color.a = 0;
			swap(this->particles[i], this->particles[this->nrOfActiveParticles - 1]);
			swap(this->vertices[i], this->vertices[this->nrOfActiveParticles - 1]);
			this->nrOfActiveParticles--;
		}
		else 
		{
			this->vertices[i].position += p.dirVec * p.speed;
			//float alphaRatio = p.lifetime / p.initialLifetime;
			this->vertices[i].color.a = (sf::Uint8) (255 * (p.lifetime / p.initialLifetime));
		}
	}
	if (this->debug)
	{
		info.setText("[Active Particles: " + std::to_string(this->nrOfActiveParticles) + "]   [VertexCount: " + std::to_string(this->vertices.getVertexCount()) + "]");
	}
}

void ParticleHandler::render(sf::RenderWindow * window)
{

	window->draw(this->vertices);
	if (this->debug)
	{
		window->draw(info.getDrawable());
	}
}

void ParticleHandler::spawnParticle(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime)
{
	if (this->nrOfActiveParticles < this->MAX_PARTICLES)
	{
		this->particles[this->nrOfActiveParticles].position = position;
		this->particles[this->nrOfActiveParticles].dirVec = dirVec;
		this->particles[this->nrOfActiveParticles].color = color;
		this->particles[this->nrOfActiveParticles].speed = speed;
		this->particles[this->nrOfActiveParticles].lifetime = lifetime;
		this->particles[this->nrOfActiveParticles].initialLifetime = lifetime;

		this->vertices[this->nrOfActiveParticles].position = position;
		this->vertices[this->nrOfActiveParticles].color = color;

		this->nrOfActiveParticles++;
	}
	
}

void ParticleHandler::spawnParticleWithRandomDirection(sf::Vector2f position, sf::Color color, float speed, float lifetime)
{
	if (this->nrOfActiveParticles < this->MAX_PARTICLES)
	{
		this->particles[this->nrOfActiveParticles].position = position;
		this->particles[this->nrOfActiveParticles].dirVec = (Utility::getRandomVector(-100.f, 100.f) / 100.f);
		this->particles[this->nrOfActiveParticles].color = color;
		this->particles[this->nrOfActiveParticles].speed = speed;
		this->particles[this->nrOfActiveParticles].lifetime = lifetime;
		this->particles[this->nrOfActiveParticles].initialLifetime = lifetime;

		this->vertices[this->nrOfActiveParticles].position = position;
		this->vertices[this->nrOfActiveParticles].color = color;

		this->nrOfActiveParticles++;
	}
}

int ParticleHandler::getNrOfParticles() const
{
	return this->nrOfActiveParticles;
}


template<typename T>
void ParticleHandler::swap(T& p1, T& p2)
{
	T temp = p1;
	p1 = p2;
	p2 = temp;
}
