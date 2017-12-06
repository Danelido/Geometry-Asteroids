#include "CustomButton.h"

CustomButton::CustomButton(std::string text, sf::Vector2f size, ParticleHandler * particlehandler)
{
	this->text.setText(text);
	this->size = size;
	this->particlehandler = particlehandler;
	this->position = sf::Vector2f(0, 0);
	this->windowSize = sf::Vector2u(0, 0);

	this->hovered = false;
	this->centerX = false;
	this->centerY = false;

	// Initialize shape
	this->shape.setSize(this->size);
	
	//TODO: make textclass able to center itself withing a specific bound
}

CustomButton::~CustomButton()
{
}

void CustomButton::update(float dt, sf::Vector2i mousePos, sf::Vector2u windowSize)
{
	if (this->windowSize != windowSize)
	{
		this->windowSize = windowSize;
		// re-center everything
	}
}

void CustomButton::render(sf::RenderWindow * window)
{
	window->draw(this->shape);
}

void CustomButton::setText(std::string text)
{
	this->text.setText(text);
	// re-center text
}

void CustomButton::setTextSize(unsigned int textSize)
{
	this->text.setTextSize(textSize);
	// re-center text
}

void CustomButton::setSize(sf::Vector2f size)
{
	this->size = size;
	// re-center everything
}

void CustomButton::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void CustomButton::setX(float x)
{
	if (this->centerX)
	{
		this->centerX = false;
	}

	this->position.x = x;
}

void CustomButton::setY(float y)
{
	if (this->centerY)
	{
		this->centerY = false;
	}

	this->position.y = y;
}

void CustomButton::centerHorizontal()
{
	this->centerX = true;
}

void CustomButton::centerVertical()
{
	this->centerY = true;
}

bool CustomButton::isHovered() const
{
	return false;
}

void CustomButton::makeEffect()
{

}