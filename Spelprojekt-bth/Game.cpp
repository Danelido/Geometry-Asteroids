#include "Game.h"
#include <cstdlib>
#include <iostream>
#include "ResourceManager.h"

Game::Game(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle)
{
	srand(static_cast<unsigned>(time(0)));
	initialize(windowWidth, windowHeight, windowTitle);
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

void Game::quit()
{
	this->window->close();
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

void Game::initialize(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle)
{
	this->window = new sf::RenderWindow();
	this->window->create(sf::VideoMode(windowWidth, windowHeight), windowTitle);
	this->window->setFramerateLimit(60);
	this->initializeResources();
}

void Game::initializeResources()
{
	ResourceManager::addFont("StandardFont", "Resources/Font/PajamaPants.ttf");
	ResourceManager::addTexture("Quad", "Resources/Textures/Quad.png");
	ResourceManager::addTexture("Circle", "Resources/Textures/Circle.png");
	ResourceManager::addTexture("Triangle", "Resources/Textures/Triangle.png");
	ResourceManager::addTexture("Background", "Resources/Textures/Background.png");
}

void Game::input()
{
	sf::Event evnt;
	while (this->window->pollEvent(evnt))
	{
		if (this->window->hasFocus())
		{
			if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->quit();
			}
			if (evnt.type == sf::Event::Resized)
			{
				if (this->window->getSize().x <= 800)
				{
					this->window->setSize(sf::Vector2u(800, this->window->getSize().y));
				}
				if (this->window->getSize().y <= 600)
				{
					this->window->setSize(sf::Vector2u(this->window->getSize().x, 600));
				}
				this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y))));
				this->stateHandler.updateViewport();
			}

			this->stateHandler.input();
		}
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

