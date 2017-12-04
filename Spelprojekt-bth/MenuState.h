#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"

class MenuState : public State
{
private:

public:
	MenuState(Game* game);
	~MenuState();

	void input();
	void update(float dt);
	void render();


};

#endif
