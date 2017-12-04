#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Projectile
{
private:
	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f position;
	sf::Vector2f dirVec;
	bool active;
	float speed;
	float radius;

public:
	Projectile();
	~Projectile();

	void update(float dt);
	void render(sf::RenderWindow* window);

	void activate(sf::Vector2f position, sf::Vector2f dirVec);
	void deActivate();

	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
	sf::Color getColor() const;
	float getSize() const;
	bool isActive() const;

};

#endif
