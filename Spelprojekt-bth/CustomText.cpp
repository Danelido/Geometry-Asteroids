#include "CustomText.h"

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
	this->text->setPosition(position);
}

void CustomText::setText(std::string string)
{
	this->text->setString(string);
}

void CustomText::setTextSize(unsigned int textSize)
{
	this->text->setCharacterSize(textSize);
}

void CustomText::centerTextOnScreen(sf::Vector2u windowSize)
{
	this->text->setPosition(
		static_cast<float>((windowSize.x / 2)),
		static_cast<float>((windowSize.y / 2)));
}

sf::Text & CustomText::getDrawable() const
{
	return *this->text;
}
