#include "Game.h"
#include "PlayState.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.changeState(new PlayState(&game));
	game.runGameLoop();
	return 0;
}