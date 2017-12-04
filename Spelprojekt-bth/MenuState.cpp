#include "MenuState.h"
#include <iostream>
#include "Game.h"
#include "PlayState.h"

MenuState::MenuState(Game * game) : State(game)
{
	std::cout << "MenuState" << std::endl;
}

MenuState::~MenuState()
{
}

void MenuState::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->game->changeState(new PlayState(this->game));
	}
}

void MenuState::update(float dt)
{
}

void MenuState::render()
{
}
