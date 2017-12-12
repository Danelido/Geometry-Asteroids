#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "CustomText.h"

class ParticleHandler
{

private:
	struct Particle 
	{
		sf::Vector2f position = sf::Vector2f(0,0);
		sf::Vector2f dirVec = sf::Vector2f(0, 0);
		sf::Color color = sf::Color(0,0,0,0);
		float lifetime = 0.f;
		float initialLifetime = 0.f;
		float speed = 0.f;
	};
private:
	int nrOfActiveParticles;
	static const int MAX_PARTICLES = 2000;
	Particle particles[MAX_PARTICLES];

	sf::VertexArray vertices;
	bool debug;
	CustomText info;

	template<typename T>
	void swap(T& p1, T& p2);

public:
	ParticleHandler();
	~ParticleHandler();

	void update(float dt);
	void render(sf::RenderWindow* window);
	void spawnParticle(sf::Vector2f position, sf::Vector2f dirVec, sf::Color color, float speed, float lifetime);
	void spawnParticleWithRandomDirection(sf::Vector2f position, sf::Color color, float speed, float lifetime);

	int getNrOfParticles() const;
};


#endif
