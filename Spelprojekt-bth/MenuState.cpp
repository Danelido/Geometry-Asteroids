#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"

#include <iostream>

MenuState::MenuState(Game * game) : State(game)
{
	
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

void MenuState::updateViewport()
{
}
