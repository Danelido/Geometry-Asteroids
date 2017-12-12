#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"
#include "CustomButton.h"
#include "ParticleHandler.h"

class MenuState : public State
{
private:
	ParticleHandler* particleHandler;
	CustomText Title;
	CustomButton* playButton;
	CustomButton* scoreButton;
	CustomButton* exitButton;

	sf::Vector2i mousePos;
public:
	MenuState(Game* game);
	~MenuState();

	void input();
	void update(float dt);
	void render();
	void updateViewport();
};

#endif
