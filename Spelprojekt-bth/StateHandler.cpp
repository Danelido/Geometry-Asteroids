#include "StateHandler.h"

StateHandler::StateHandler()
{

}

StateHandler::~StateHandler()
{
	for (int i = 0; i < this->states.size(); i++)
	{
		delete this->states.at(i);
	}
}

void StateHandler::popCurrentState()
{
	if (!this->states.empty())
	{
		delete this->states.back();
		this->states.pop_back();
	}
}

void StateHandler::pushState(State * state)
{		
	this->states.push_back(state);
}

void StateHandler::changeState(State * state)
{
	if (!this->states.empty())
	{
		for (int i = 0; i < this->states.size(); i++)
		{
			this->popCurrentState();
		}
	}

	this->pushState(state);
}

void StateHandler::input()
{
	if (!this->states.empty())
	{
		this->states.back()->input();
	}
}

void StateHandler::update(float dt)
{
	if (!this->states.empty())
	{
		this->states.back()->update(dt);
	}
}

void StateHandler::render()
{
	if (!this->states.empty())
	{
		this->states.back()->render();
	}
}

void StateHandler::updateViewport()
{
	if (!this->states.empty())
	{
		this->states.back()->updateViewport();
	}
}
