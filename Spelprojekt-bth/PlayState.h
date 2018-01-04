#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "State.h"
#include "Player.h"
#include "ProjectileHandler.h"
#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "CustomText.h"

class PlayState : public State
{
private:
	Player* player;
	ParticleHandler* particleHandler;
	ProjectileHandler* projectionHandler;
	ObstacleHandler* obstacleHandler;
	sf::Vector2f mousePos;
	sf::RectangleShape background;
	CustomText playerScoreText;
	CustomText destroyedObstaclesText;
	CustomText gameInfo;

	float gameCountdown;
	bool startCountdown;

	float fireRate;
	float fireTimer;
	bool isShooting;
	
	bool canAddEnemies;

	void handleShooting(float dt);
	void playLogic(float dt);
	void handleGameinfo(float dt);
public:
	PlayState(Game* game);
	~PlayState();

	void input() override;
	void update(float dt) override;
	void render() override;
	void updateViewport() override;
};


#endif
