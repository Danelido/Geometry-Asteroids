#include "Game.h"
#include "MenuState.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.changeState(new MenuState(&game));
	game.runGameLoop();
	return 0;
}