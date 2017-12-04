#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Particle
{

private:
	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f dirVec;
	sf::Vector2f position;
	float currentLifetime;
	float totalLifetime;
	float speed;

public:
	Particle();
	~Particle();

	void update(float dt);
	void render(sf::RenderWindow* window);

	void activate(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime);
	bool isActive() const;

};


#endif
