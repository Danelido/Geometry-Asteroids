#include "Player.h"
#include "ParticleHandler.h"
#include <SFML/Window/Event.hpp>
#include "Utility.h"

Player::Player(float size, float health, sf::Vector2u windowSize, ParticleHandler* particleHandler)
{
	this->size = size;
	this->health = health;
	this->windowSize = windowSize;
	this->particleHandler = particleHandler;

	this->initiate();
	
}

Player::~Player()
{
	
}

void Player::initiate()
{
	this->position = sf::Vector2f(0, 0);
	this->dirVec = sf::Vector2f(0, 0);
	this->velocity = sf::Vector2f(0, 0);

	this->accelerationRate = 11.75f;
	this->deaccelerationRate = 21.75f;

	this->maxSpeed = 10.f;
	this->angle = 0.0f;
	this->immune = false;
	this->isMoving = false;
	this->color = sf::Color(0, 255, 0, 255);

	this->playerShape.setPointCount(3);
	this->playerShape.setOrigin(sf::Vector2f(this->size, this->size));
	this->playerShape.setFillColor(this->color);
	this->playerShape.setRadius(size);
	this->playerShape.setRotation(this->angle);

	// Setup health bar
	this->healthBarBase.setSize(sf::Vector2f(this->health, 35.f));
	this->healthBarBase.setFillColor(sf::Color::Red);
	this->healthBarBase.setOutlineThickness(1.f);
	this->healthBarBase.setOutlineColor(sf::Color::White);
	this->healthBarBase.setPosition(sf::Vector2f(10.f, 80.f));

	this->healthBar.setSize(sf::Vector2f(this->health, 35));
	this->healthBar.setFillColor(sf::Color::Green);
	this->healthBar.setPosition(sf::Vector2f(10.f,80.f));

}

void Player::update(float dt)
{
	if (this->immune)
	{
		this->playerShape.setFillColor(sf::Color::Blue);
		if (this->immuneTime > 0.0f)
		{
			this->immuneTime -= dt;
		}
		else
		{
			this->immune = false;
			this->immuneTime = 0.0f;
			this->playerShape.setFillColor(sf::Color::White);
		}
	}
	this->movementLogic(dt);
	this->playerShape.setPosition(this->position);
	this->playerShape.setRotation(this->angle);
}

void Player::movementLogic(float dt)
{
	// IF MOVING
	if (this->isMoving)
	{
		// right
		if (this->dirVec.x > 0.0f)
		{
			if (this->velocity.x < (this->dirVec.x * this->maxSpeed))
			{
				this->velocity.x += this->accelerationRate * this->dirVec.x * dt;
			}
		}// left
		else if (this->dirVec.x < 0.0f)
		{
			if (this->velocity.x > (this->dirVec.x * this->maxSpeed))
			{
				this->velocity.x += this->accelerationRate * this->dirVec.x * dt;
			}
		}

		// up
		if (this->dirVec.y > 0.0f)
		{
			if (this->velocity.y < (this->dirVec.y * this->maxSpeed))
			{
				this->velocity.y += this->accelerationRate * this->dirVec.y * dt;
			}
		}// down
		else if (this->dirVec.y < 0.0f)
		{
			if (this->velocity.y > (this->dirVec.y * this->maxSpeed))
			{
				this->velocity.y += this->accelerationRate * this->dirVec.y * dt;
			}
		}

		this->movementEffect(this->dirVec);

	}// IF NOT MOVING SLOW DOWN
	else if (!this->isMoving)
	{
		// Decrease vel on x-axis
		if (this->velocity.x > 0.0f)
		{
			this->velocity.x -= this->deaccelerationRate * abs(this->velocity.x / this->maxSpeed) * dt;
			
			if (this->velocity.x <= 0.0f)
			{
				this->velocity.x = 0;
			}
		}// increase vel on x-axis
		else if (this->velocity.x < 0.0f)
		{
			this->velocity.x += this->deaccelerationRate * abs(this->velocity.x / this->maxSpeed) * dt;
			
			if (this->velocity.x >= 0.0f)
			{
				this->velocity.x = 0.0f;
			}
		}

		// decrease vel on y-axis
		if (this->velocity.y > 0.0f)
		{
			this->velocity.y -= this->deaccelerationRate * abs(this->velocity.y / this->maxSpeed) * dt;
			
			if (this->velocity.y <= 0.0f)
			{
				this->velocity.y = 0.0f;
			}
		}// increase vel on y-axis
		else if (this->velocity.y < 0.0f)
		{
			this->velocity.y += this->deaccelerationRate * abs(this->velocity.y / this->maxSpeed) * dt;
			
			if (this->velocity.y >= 0.0f)
			{
				this->velocity.y = 0.0f;
			}
		}

	}

	// before updating position check if player still is inside the world, if not, reverse and decrease velocity
	// This will make it more of a bouncy effect
	// TODO: Get window size and simplify
	if (this->position.x + this->size >= static_cast<float>(this->windowSize.x))
	{
		this->position.x = static_cast<float>(this->windowSize.x) - this->size;
		if (this->velocity.x > 0)
		{
			this->velocity.x = -this->velocity.x * 0.25f;
		}
	}
	else if (this->position.x - this->size <= 0)
	{
		this->position.x = this->size;
		if (this->velocity.x < 0)
		{
			this->velocity.x = -this->velocity.x * 0.25f;
		}
	}
	if (this->position.y + this->size >= static_cast<float>(this->windowSize.y))
	{
		this->position.y = static_cast<float>(this->windowSize.y) - this->size;
		if (this->velocity.y > 0)
		{
			this->velocity.y = -this->velocity.y * 0.25f;
		}
	}
	else if (this->position.y - this->size <= 0)
	{
		this->position.y = this->size;
		if (this->velocity.y < 0)
		{
			this->velocity.y = -this->velocity.y * 0.25f;
		}
	}

	this->position += this->velocity;
}

void Player::movementEffect(sf::Vector2f playerDirection)
{
	for (int i = 0; i < 10; i++)
	{
		if (playerDirection.x < 0.0f)
		{
			playerDirection.x = Utility::getRandomNumber(10.f, 90.f);
		}
		else
		{
			playerDirection.x = Utility::getRandomNumber(-90.f, -10.f);
		}

		if (playerDirection.y < 0.0f)
		{
			playerDirection.y = Utility::getRandomNumber(10.f, 90.f);
		}
		else
		{
			playerDirection.y = Utility::getRandomNumber(-90.f, -10.f);
		}
		playerDirection /= 90.f;

		this->particleHandler->spawnParticle(
			(position - ((this->size / 2.f - 5.f) * this->dirVec)),
			playerDirection,
			sf::Color(Utility::getRandomNumber(100, 255), Utility::getRandomNumber(100, 255), Utility::getRandomNumber(100, 255), 255),
			1.5f, 0.5f);

	}
}

void Player::render(sf::RenderWindow* window)
{
	window->draw(this->playerShape);
	window->draw(this->healthBarBase);
	window->draw(this->healthBar);
}

void Player::setDirectionMultiplier(sf::Vector2f directionMultiplier)
{
	this->dirVec = (directionMultiplier);
}

Player & Player::shouldMove(bool move)
{
	this->isMoving = move;

	return *this;
}

void Player::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Player::setHealth(float health)
{
	this->health = health;
	if (this->health <= 0.0f)
	{
		this->health = 0.0f;
	}
	this->color = sf::Color(
		255 - (sf::Uint8)((this->health / 100.f)* 255.f),
		(sf::Uint8)((this->health / 100.f)* 255.f),
		0,
		255);
	this->playerShape.setFillColor(this->color);
	this->healthBar.setSize(sf::Vector2f(this->health, this->healthBar.getSize().y));
}

void Player::setAngle(float angle)
{
	this->angle = angle;
}

void Player::setImmune()
{
	this->immuneTime = 3.0f;
	this->immune = true;
}

void Player::incrementScore(float value)
{
	this->score += value;
}

void Player::updateViewport(sf::Vector2u windowSize)
{
	this->windowSize = windowSize;
}

bool Player::isImmune() const
{
	return this->immune;
}

float Player::getHealth() const
{
	return this->health;
}

sf::Vector2f Player::getPosition() const
{
	return this->position;
}

float Player::getSize() const
{
	return this->size;
}

int Player::getScore() const
{
	return static_cast<int>(this->score);
}
