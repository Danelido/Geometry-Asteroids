#include "CustomText.h"
#include <iostream>

CustomText::CustomText(std::string string, sf::Vector2f position, unsigned int fontSize, sf::Color color)
{
	this->font = new sf::Font();

	if (!this->font->loadFromFile("Resources/Font/PajamaPants.ttf"))
	{
		std::printf("Failed to load font!");
	}

	this->text = new sf::Text();
	this->text->setFont(*this->font);
	this->text->setString(string);
	this->text->setCharacterSize(fontSize);

	this->text->setFillColor(color);
	this->text->setPosition(position);

	this->windowSize = sf::Vector2u(0, 0); // initialize it to zero
	this->isCentered = false;

}

CustomText::~CustomText()
{
	delete this->font;
	delete this->text;
}

void CustomText::setColor(sf::Color color)
{
	this->text->setFillColor(color);
}

void CustomText::setPosition(sf::Vector2f position)
{
	// If it was supposed to be centered and the user uses this function
	// that person obviusly doesnt want it to be centered anymore
	if (this->isCentered)
	{
		this->isCentered = false;
	}
	this->text->setPosition(position);
}

void CustomText::setText(std::string string)
{
	if (this->text->getString() != string)
	{
		this->text->setString(string);

		if (isCentered)
		{
			// Recenter the text if it is supposed to be centered
			this->text->setPosition(
				static_cast<float>(windowSize.x / 2) - round(this->text->getGlobalBounds().width / 2),
				static_cast<float>(windowSize.y / 2) - round(this->text->getGlobalBounds().height / 2));
		}
	}
}

void CustomText::setTextSize(unsigned int textSize)
{
	this->text->setCharacterSize(textSize);
}

void CustomText::centerTextOnScreen(sf::Vector2u windowSize)
{
	// This means that the text is supposed to be centered
	this->isCentered = true;
	if (this->windowSize != windowSize)
	{
		this->windowSize = windowSize;
		this->text->setPosition(
			static_cast<float>(windowSize.x / 2) - round(this->text->getGlobalBounds().width / 2),
			static_cast<float>(windowSize.y / 2) - round(this->text->getGlobalBounds().height / 2));
	}
}

sf::Vector2f CustomText::getSize() const
{
	return sf::Vector2f(this->text->getGlobalBounds().width, this->text->getGlobalBounds().height);
}

sf::Text & CustomText::getDrawable() const
{
	return *this->text;
}
