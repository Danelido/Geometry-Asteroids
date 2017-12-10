#ifndef SCORESTATE_H
#define SCORESTATE_H
#include "State.h"
#include "ParticleHandler.h"
#include "CustomButton.h"


class ScoreState : public State
{
private:
	CustomText highScoreText;
	CustomText infoText;
	ParticleHandler* particleHandler;
	CustomButton * backToMenuButton;

	sf::Vector2i mousePos;
	int highScore;
	int score;

	void getHighscoreFromFile(std::string path);
	void saveNewHighscoreToFile(std::string path, int newHighscore) throw(...);
public:
	ScoreState(Game* game, int score = 0);
	virtual ~ScoreState();

	void input();
	void update(float dt);
	void render();
	void updateViewport();

};

#endif
