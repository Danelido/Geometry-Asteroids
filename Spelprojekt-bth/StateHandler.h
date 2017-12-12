#ifndef STATEHANDLER_H
#define STATEHANDLER_H
#include "State.h"
#include <vector>

class StateHandler
{

private:
	std::vector<State*> states;
public:
	StateHandler();
	~StateHandler();

	void popCurrentState();
	void pushState(State* state);
	void changeState(State* state);

	void input();
	void update(float dt);
	void render();

	void updateViewport();
};

#endif
