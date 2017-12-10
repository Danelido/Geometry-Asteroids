#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "ScoreState.h"
#include <iostream>

MenuState::MenuState(Game * game) : State(game)
{
	this->mousePos = sf::Vector2i(0, 0);
	this->particleHandler = new ParticleHandler();
	
	this->Title.setText("Asteroids but different");
	this->Title.setColor(sf::Color::White);
	this->Title.setTextSize(45);
	this->Title.centerWithinBounds(sf::FloatRect(0.f, 50.f, (float)(this->game->getWindow()->getSize().x), this->game->getWindow()->getSize().y / 2.f - 200));

	this->playButton = new CustomButton("Play", sf::Vector2f(145, 65), this->particleHandler);
	this->playButton->centerHorizontal();
	this->playButton->setY(this->game->getWindow()->getSize().y / 2.f - 150);
	this->playButton->setTextSize(30);

	this->scoreButton = new CustomButton("Score", sf::Vector2f(145, 65), this->particleHandler);
	this->scoreButton->centerHorizontal();
	this->scoreButton->setY(this->game->getWindow()->getSize().y / 2.f);
	this->scoreButton->setTextSize(30);
	this->scoreButton->setParticleColor(sf::Color::Yellow);

	this->exitButton = new CustomButton("Exit", sf::Vector2f(145, 65), this->particleHandler);
	this->exitButton->centerHorizontal();
	this->exitButton->setY(this->game->getWindow()->getSize().y / 2.f + 150);
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
			this->game->changeState(new ScoreState(this->game));
		}
		else if (this->exitButton->isHovered())
		{
			this->game->quit();
		}
	}
	else
	{

		//Play
		if (this->playButton->isHovered())
		{
			this->playButton->setTextColor(sf::Color(0, 255, 0, 150));
		}
		else
		{
			this->playButton->setTextColor(sf::Color(255, 255, 255, 255));
		}
		//Score
		if (this->scoreButton->isHovered())
		{
			this->scoreButton->setTextColor(sf::Color(255, 255, 0, 150));
		}
		else
		{
			this->scoreButton->setTextColor(sf::Color(255, 255, 255, 255));
		}
		// Exit
		if (this->exitButton->isHovered())
		{
			this->exitButton->setTextColor(sf::Color(255, 0, 0, 150));
		}
		else
		{
			this->exitButton->setTextColor(sf::Color(255, 255, 255, 150));
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
	this->game->getWindow()->draw(this->Title.getDrawable());
	this->playButton->render(this->game->getWindow());
	this->scoreButton->render(this->game->getWindow());
	this->exitButton->render(this->game->getWindow());
}

void MenuState::updateViewport()
{
	this->Title.centerWithinBounds(sf::FloatRect(0.f, 50.f, (float)(this->game->getWindow()->getSize().x), this->game->getWindow()->getSize().y / 2.f - 200));
	this->playButton->setY(this->game->getWindow()->getSize().y / 2.f - 150);
	this->scoreButton->setY(this->game->getWindow()->getSize().y / 2.f);
	this->exitButton->setY(this->game->getWindow()->getSize().y / 2.f + 150);
}
