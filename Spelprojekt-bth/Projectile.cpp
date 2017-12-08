#include "Projectile.h"

Projectile::Projectile()
{
	this->color = sf::Color::Yellow;
	
	this->speed = 1350.f;
	this->radius = 4.f;

	this->shape.setRadius(this->radius);
	this->shape.setFillColor(this->color);
	this->shape.setOrigin(sf::Vector2f(this->radius, this->radius));
}

Projectile::~Projectile()
{
}

void Projectile::update(float dt)
{
	this->position += this->dirVec * this->speed * dt;
	this->shape.setPosition(this->position);
}

void Projectile::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
}

void Projectile::activate(sf::Vector2f position, sf::Vector2f dirVec)
{
	this->position = position;
	this->dirVec = dirVec;
	this->active = true;
}

void Projectile::deActivate()
{
	this->active = false;
}

sf::Vector2f Projectile::getPosition() const
{
	return this->position;
}

sf::Vector2f Projectile::getDirection() const
{
	return this->dirVec;
}

sf::Color Projectile::getColor() const
{
	return this->color;
}

float Projectile::getSize() const
{
	return (this->radius * 2.f);
}

bool Projectile::isActive() const
{
	return this->active;
}
