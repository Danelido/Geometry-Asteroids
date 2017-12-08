#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"

#include <iostream>

MenuState::MenuState(Game * game) : State(game)
{
	this->mousePos = sf::Vector2i(0, 0);
	this->particleHandler = new ParticleHandler();
	
	this->playButton = new CustomButton("Play", sf::Vector2f(145, 65), this->particleHandler);
	this->playButton->centerHorizontal();
	this->playButton->setY(150.f);
	this->playButton->setTextSize(30);

	this->scoreButton = new CustomButton("Score", sf::Vector2f(145, 65), this->particleHandler);
	this->scoreButton->centerHorizontal();
	this->scoreButton->setY(300.f);
	this->scoreButton->setTextSize(30);
	this->scoreButton->setParticleColor(sf::Color::Yellow);

	this->exitButton = new CustomButton("Exit", sf::Vector2f(145, 65), this->particleHandler);
	this->exitButton->centerHorizontal();
	this->exitButton->setY(450.f);
	this->exitButton->setTextSize(30);
	this->exitButton->setParticleColor(sf::Color::Red);
}

MenuState::~MenuState()
{
	delete this->playButton;
	delete this->scoreButton;
	delete this->exitButton;
	delete this->particleHandler;
}

void MenuState::input()
{
	this->mousePos = sf::Mouse::getPosition(*this->game->getWindow());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (this->playButton->isHovered())
		{
			this->game->changeState(new PlayState(this->game));
		}
		else if (this->scoreButton->isHovered())
		{
			
		}
		else if (this->exitButton->isHovered())
		{
			
		}
	}

}

void MenuState::update(float dt)
{	
	this->playButton->update(dt, this->mousePos, this->game->getWindow()->getSize());
	this->scoreButton->update(dt, this->mousePos, this->game->getWindow()->getSize());
	this->exitButton->update(dt, this->mousePos, this->game->getWindow()->getSize());
	this->particleHandler->update(dt);
	
}

void MenuState::render()
{
	this->particleHandler->render(this->game->getWindow());
	this->playButton->render(this->game->getWindow());
	this->scoreButton->render(this->game->getWindow());
	this->exitButton->render(this->game->getWindow());
}

void MenuState::updateViewport()
{
}
