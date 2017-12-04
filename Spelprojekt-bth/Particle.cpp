#include "Particle.h"

Particle::Particle()
{
	this->shape.setRadius(2.f);
}

Particle::~Particle()
{
}

void Particle::update(float dt)
{
		this->currentLifetime -= dt;
		
		if (this->currentLifetime <= 0.0f)
		{
			this->currentLifetime = 0.0f;
		}
		this->color.a = (sf::Uint8) (255 * (this->currentLifetime / this->totalLifetime));
		this->position += this->dirVec * this->speed;
		this->shape.setFillColor(this->color);
		this->shape.setPosition(this->position);
		
}

void Particle::render(sf::RenderWindow * window)
{
		window->draw(this->shape);
}

void Particle::activate(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime)
{
	this->position = position;
	this->dirVec = dirVec;
	this->color = color;
	this->speed = speed;
	
	this->currentLifetime = lifetime;
	this->totalLifetime = lifetime;

	this->shape.setPosition(this->position);
	this->shape.setFillColor(this->color);
	
	
}

bool Particle::isActive() const
{
	return (this->currentLifetime > 0.0f);
}
