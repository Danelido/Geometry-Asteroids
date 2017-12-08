#ifndef OBSTACLEHANDLER_H
#define OBSTACLEHANDLER_H
#include "Obstacle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"

class Player;
class ParticleHandler;


class ObstacleHandler
{
private:
	sf::Vector2u windowSize;
	int nrOfObstacles;
	int maxObstacles;
	Obstacle** obstacles;
	Player* player;
	ParticleHandler* particleHandler;
	int nrOfObstaclesDestroyed; // this is used for player score

	void initiateArray();
	bool collisionWithPlayer();
	void checkIfOutOfBounds(int index);
	void makeEffect(int index);
	void freeMemory();
public:
	ObstacleHandler(Player* player, ParticleHandler* particleHandler, sf::Vector2u windowSize);
	~ObstacleHandler();

	void update(float dt);
	void render(sf::RenderWindow* window);

	void addCircleObstacle();
	void addRectangleObstacle();
	void addTriangleObject();

	//DEBUG & TEST
	void addDummy();

	void decreaseLife(int index);
	void removeAllObstacles();

	int getNrOfObstacles() const;
	int getNrOfDestroyedObstacles() const;
	Obstacle** getArray() const;

	void updateViewport(sf::Vector2u windowSize);

};

#endif
