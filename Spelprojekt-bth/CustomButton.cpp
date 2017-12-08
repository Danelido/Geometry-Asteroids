#include "CustomButton.h"
#include <iostream>
#include "Utility.h"

CustomButton::CustomButton(std::string text, sf::Vector2f size, ParticleHandler * particlehandler, sf::Vector2f position)
{
	this->text.setText(text);
	this->size = size;
	this->originalSize = size;
	this->position = position;
	this->originalPosition = position;
	this->particlehandler = particlehandler;
	this->windowSize = sf::Vector2u(0, 0);

	this->hovered = false;
	this->centerX = false;
	this->centerY = false;
	this->timer = 0.f;
	this->sizeSpeed = 1.2f;

	// Initialize shape
	this->shape.setPosition(this->position);
	this->shape.setSize(this->size);
	this->shape.setOutlineThickness(1.f);
	this->shape.setFillColor(sf::Color(0, 0, 0, 235));
	this->shape.setOutlineColor(sf::Color::White);
	
	this->particleColor = sf::Color::Green;

	this->adjustButton();
}

CustomButton::~CustomButton()
{
}

void CustomButton::update(float dt, sf::Vector2i mousePos, sf::Vector2u windowSize)
{
	if (this->windowSize != windowSize)
	{
		this->windowSize = windowSize;
		this->adjustButton();
	}

	// Check if mouse is on top of button
	if (mousePos.x >= this->position.x && mousePos.x <= this->position.x + this->size.x &&
		mousePos.y >= this->position.y && mousePos.y <= this->position.y + this->size.y)
	{
		this->hovered = true;
	}
	else
	{
		this->hovered = false;
	}

	this->makeEffect(dt);

}

void CustomButton::render(sf::RenderWindow * window)
{
	window->draw(this->shape);
	window->draw(this->text.getDrawable());
}

void CustomButton::adjustButton()
{
	
		this->shape.setSize(this->size);

		if (this->centerX)
		{
			this->position.x = static_cast<float>(windowSize.x / 2) - round(this->shape.getGlobalBounds().width / 2);
			this->originalPosition.x = position.x;
		}

		if (this->centerY)
		{
			this->position.y = static_cast<float>(windowSize.y / 2) - round(this->shape.getGlobalBounds().height / 2);
			this->originalPosition.y = position.y;
		}

		this->shape.setPosition(this->position);
		this->text.centerWithinBounds(this->shape.getGlobalBounds());
	
}

void CustomButton::setText(std::string text)
{
	this->text.setText(text);
	this->adjustButton();
}

void CustomButton::setTextSize(unsigned int textSize)
{
	this->text.setTextSize(textSize);
	this->adjustButton();
}

void CustomButton::setTextColor(sf::Color color)
{
	this->text.setColor(color);
}

void CustomButton::setSize(sf::Vector2f size)
{
	this->size = size;
	this->originalSize = size;
	this->adjustButton();
}

void CustomButton::setPosition(sf::Vector2f position)
{
	if (this->centerX)
	{
		this->centerX = false;
	}
	if (this->centerY)
	{
		this->centerY = false;
	}

	this->position = position;
	this->originalPosition = position;
	this->adjustButton();
}

void CustomButton::setBoxColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void CustomButton::setX(float x)
{
	if (this->centerX)
	{
		this->centerX = false;
	}

	this->position.x = x;
	this->originalPosition.x = x;
	this->adjustButton();
}

void CustomButton::setY(float y)
{
	if (this->centerY)
	{
		this->centerY = false;
	}

	this->position.y = y;
	this->originalPosition.y = y;
	this->adjustButton();
}

void CustomButton::setParticleColor(sf::Color color)
{
	this->particleColor = color;
}

void CustomButton::centerHorizontal()
{
	this->centerX = true;
	this->adjustButton();
}

void CustomButton::centerVertical()
{
	this->centerY = true;
	this->adjustButton();
}


bool CustomButton::isHovered() const
{
	return this->hovered;
}

void CustomButton::makeEffect(float dt)
{
	if (this->hovered)
	{
		this->timer += (dt + 0.08f);
		this->size.x += sizeSpeed * sin(timer);
		this->size.y += (sizeSpeed * sin(timer)) / 2.f;

		this->position.x -= (sizeSpeed * sin(timer)) / 2.f;
		this->position.y -= (sizeSpeed * sin(timer)) / 4.f;

		sf::Uint8 colorVal = (sf::Uint8) (60 * sin(timer) + 180);

		this->shape.setOutlineColor(sf::Color(colorVal, colorVal, colorVal, 230));
		this->shape.setSize(this->size);
		this->shape.setPosition(this->position);

		for (int i = 0; i < 4; i++)
		{

			int spawnpoint = Utility::getRandomNumber(1, 4);

			//Top
			if (spawnpoint == 1)
			{
				this->particlehandler->spawnParticle(
					sf::Vector2f(Utility::getRandomNumber(this->position.x, this->position.x + this->size.x), this->position.y),
					Utility::getRandomVector(-100.f, 100.f, -100.f, 0.f) / 100.f,
					this->particleColor,
					Utility::getRandomNumber(110.f, 142.f) / 100.f,
					Utility::getRandomNumber(120.f, 200.f) / 100.f);
			}

			//Right side
			else if (spawnpoint == 2)
			{
				this->particlehandler->spawnParticle(
					sf::Vector2f(this->position.x + this->size.x, Utility::getRandomNumber(this->position.y, this->position.y + this->size.y)),
					Utility::getRandomVector(0.f, 100.f, -100.f, 100.f) / 100.f,
					this->particleColor,
					Utility::getRandomNumber(110.f, 142.f) / 100.f,
					Utility::getRandomNumber(120.f, 200.f) / 100.f);
			}

			//Bottom
			else if (spawnpoint == 3)
			{
				this->particlehandler->spawnParticle(
					sf::Vector2f(Utility::getRandomNumber(this->position.x, this->position.x + this->size.x), this->position.y + this->size.y),
					Utility::getRandomVector(-100.f, 100.f, 0.f, 100.f) / 100.f,
					this->particleColor,
					Utility::getRandomNumber(110.f, 142.f) / 100.f,
					Utility::getRandomNumber(120.f, 200.f) / 100.f);
			}

			//Left side
			else if (spawnpoint == 4)
			{
				this->particlehandler->spawnParticle(
					sf::Vector2f(this->position.x, Utility::getRandomNumber(this->position.y, this->position.y + this->size.y)),
					Utility::getRandomVector(-100.f, 0.f, -100.f, 100.f) / 100.f,
					this->particleColor,
					Utility::getRandomNumber(110.f, 142.f) / 100.f,
					Utility::getRandomNumber(120.f, 200.f) / 100.f);
			}
		}

	}
	else
	{
		if (this->timer != 0.f)
		{
			this->timer = 0.f;
		}

		if (this->shape.getOutlineColor() != sf::Color::White)
		{
			this->shape.setOutlineColor(sf::Color::White);
		}

		if (this->size != this->originalSize)
		{
			float decreaseRate = 1.f;
			if (this->size.x > this->originalSize.x)
			{
				this->size.x -= decreaseRate;
				this->position.x += decreaseRate / 2.f;
				if (this->size.x <= this->originalSize.x)
				{
					this->size.x = this->originalSize.x;
					this->position.x = this->originalPosition.x;
				}
			}

			else if (this->size.x < this->originalSize.x)
			{
				this->size.x += decreaseRate;
				this->position.x -= decreaseRate / 2.f;
				if (this->size.x >= this->originalSize.x)
				{
					this->size.x = this->originalSize.x;
					this->position.x = this->originalPosition.x;
				}
			}

			if (this->size.y > this->originalSize.y)
			{
				this->size.y -= decreaseRate / 2.f;
				this->position.y += decreaseRate / 4.f;
				if (this->size.y <= this->originalSize.y)
				{
					this->size.y = this->originalSize.y;
					this->position.y = this->originalPosition.y;
				}
			}

			else if (this->size.y < this->originalSize.y)
			{
				this->size.y += decreaseRate / 2.f;
				this->position.y -= decreaseRate / 4.f;
				if (this->size.y >= this->originalSize.y)
				{
					this->size.y = this->originalSize.y;
					this->position.y = this->originalPosition.y;
				}
			}
			this->adjustButton();
		}
	}

}