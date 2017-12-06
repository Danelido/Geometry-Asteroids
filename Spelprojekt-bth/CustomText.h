#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class CustomText
{
private:
	sf::Font* font;
	sf::Text* text;
	bool isCentered;
	sf::Vector2u windowSize;

public:
	CustomText(std::string string = "", sf::Vector2f position = sf::Vector2f(0.f,0.f), unsigned int textSize = 24, sf::Color color = sf::Color::White);
	~CustomText();

	void setColor(sf::Color color);
	void setPosition(sf::Vector2f position);
	void setText(std::string string);
	void setTextSize(unsigned int textSize);
	void centerTextOnScreen(sf::Vector2u windowSize);
	sf::Vector2f getSize() const;
	sf::Text& getDrawable() const;

};

#endif
