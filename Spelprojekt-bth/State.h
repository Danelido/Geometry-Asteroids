#ifndef STATE_H
#define STATE_H

class Game; // Empty class

class State
{
protected:
	Game* game; // points to the empty class above but will be initialize with the game class inside a state class

public:
	State(Game* game){	this->game = game; }
	virtual ~State(){}

	virtual void input() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void updateViewport() = 0;
};

#endif
