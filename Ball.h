#pragma once

#include <SFML/Graphics.hpp>

class World;

class Ball : public sf::RectangleShape
{
private:
	float m_Speed = 0;
	sf::Vector2f m_Velocity;
	World* m_World = nullptr;

	void copy(const Ball&);

	void normalize();

	void initializeVelocity();

	void handleBorderCollisions();

public:
	Ball() = default;

	Ball(const sf::Vector2f&, float, World&);

	Ball(const Ball&);

	~Ball();

	Ball& operator=(const Ball&);

	void init(const sf::Vector2f&, float, World&);

	void setVelocityByInversion(bool, bool);

	void update(const sf::Time&);
};