#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include "CustomText.h"
#include "ParticleHandler.h"
#include <SFML/Graphics/RectangleShape.hpp>

class CustomButton
{
private:
	sf::RectangleShape shape;
	ParticleHandler* particlehandler;
	CustomText text;
	
	sf::Vector2f position;
	sf::Vector2f originalPosition;
	sf::Vector2f size;
	sf::Vector2f originalSize;
	sf::Vector2u windowSize;
	
	bool hovered;
	bool centerX;
	bool centerY;

	float timer;
	float sizeSpeed;

	sf::Color particleColor;

	void makeEffect(float dt);
	void adjustButton();
public:

	CustomButton(std::string text, sf::Vector2f size, ParticleHandler* particlehandler, sf::Vector2f position = sf::Vector2f(0,0));
	virtual ~CustomButton();

	void update(float dt, sf::Vector2i mousePos, sf::Vector2u windowSize = sf::Vector2u(0,0));
	void render(sf::RenderWindow* window);

	void setText(std::string text);
	void setTextSize(unsigned int textSize);
	void setTextColor(sf::Color color);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setBoxColor(sf::Color color);
	void setX(float x);
	void setY(float y);
	void setParticleColor(sf::Color color);
	void centerHorizontal();
	void centerVertical();
	bool isHovered() const;

};


#endif
