#ifndef GAME_H
#define GAME_H
#include "StateHandler.h"
#include <SFML\Graphics.hpp>
#include <string>

class Game
{

private:
	std::string windowTitle;
	StateHandler stateHandler;

	void initialize(unsigned int windowWidth, unsigned int windowHeight);
	void input();
	void update(float dt);
	void render();
	sf::RenderWindow* window;

public:

	Game(unsigned int windowWidth = 1280, unsigned int windowHeight = 720, std::string windowTitle = "Window");
	~Game();

	void pushState(State* newState);
	void popCurrentState();
	void changeState(State* newState);
	void quit();
	void runGameLoop();

	sf::RenderWindow* getWindow() const;
};


#endif
