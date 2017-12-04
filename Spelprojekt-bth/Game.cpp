#include "Game.h"
#include <cstdlib>
#include <iostream>

Game::Game(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle)
{
	srand(static_cast<unsigned>(time(0)));
	this->windowTitle = windowTitle;
	initialize(windowWidth, windowHeight);
}

Game::~Game()
{
	delete this->window;
}

void Game::pushState(State * newState)
{
	this->stateHandler.pushState(newState);
}

void Game::popCurrentState()
{
	this->stateHandler.popCurrentState();
}

void Game::changeState(State * newState)
{
	this->stateHandler.changeState(newState);
}

void Game::runGameLoop()
{
	sf::Clock delta;
	while (this->window->isOpen())
	{
		this->input();
		this->update(delta.restart().asSeconds());
		this->render();
	}
}

sf::RenderWindow* Game::getWindow() const
{
	return this->window;
}

//** Private helper functions **\\

void Game::initialize(unsigned int windowWidth, unsigned int windowHeight)
{
	this->window = new sf::RenderWindow();
	this->window->create(sf::VideoMode(windowWidth, windowHeight), this->windowTitle);
	this->window->setFramerateLimit(60);
}

void Game::input()
{
	sf::Event evnt;
	while (this->window->pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->window->close();
		}
		if (evnt.type == sf::Event::Resized)
		{
			this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y))));
			this->stateHandler.updateViewport();
		}

		this->stateHandler.input();
	}
}

void Game::update(float dt)
{
	this->stateHandler.update(dt);
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	this->stateHandler.render();
	this->window->display();
}

