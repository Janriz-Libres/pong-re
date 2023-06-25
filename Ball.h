#pragma once

#include <SFML/Graphics.hpp>

class World;

class Ball : public sf::RectangleShape
{
private:
	float m_Speed = 0;
	sf::Vector2f m_Velocity;
	World* m_World = nullptr;

	void normalize();

	void initializeVelocity();

	void handlePaddleCollisions();

	void handleBorderCollisions();

public:
	Ball() = default;

	Ball(const sf::Vector2f&, float, World&);

	~Ball();

	void init(const sf::Vector2f&, float, World&);

	void update(const sf::Time&);
};