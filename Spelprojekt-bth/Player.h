#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class ParticleHandler;

class Player
{

private:
	ParticleHandler* particleHandler;
	sf::Vector2u windowSize;
	sf::CircleShape playerShape;
	sf::Color color;
	sf::RectangleShape healthBarBase;
	sf::RectangleShape healthBar;
	sf::Vector2f position;
	sf::Vector2f dirVec;
	sf::Vector2f velocity;
	
	
	float score;
	float size;
	float maxSpeed;
	float health;
	float angle;
	float accelerationRate;
	float deaccelerationRate;
	float immuneTime;
	
	bool immune;
	bool isMoving;

	void initiate();
	void movementLogic(float dt);
	void movementEffect(sf::Vector2f playerDirection);
	
public:
	Player(float size, float health, sf::Vector2u windowSize, ParticleHandler* particlehandler);
	~Player();

	void update(float dt);
	void render(sf::RenderWindow* window);

	void setDirectionMultiplier(sf::Vector2f directionMultiplier);
	Player& shouldMove(bool move);
	void setPosition(sf::Vector2f position);
	void setHealth(float health);
	void setAngle(float angle);
	void setImmune();
	void incrementScore(float value);
	void updateViewport(sf::Vector2u windowSize);

	sf::Vector2f getPosition() const;
	bool isImmune() const;
	float getHealth() const;
	float getSize() const;
	int getScore() const;

};

#endif
