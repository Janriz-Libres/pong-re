#pragma once

#include <SFML/Graphics.hpp>

class Hud;
class World;

class Ball : public sf::RectangleShape
{
private:
	static constexpr float INIT_SPEED = 900;
	static constexpr float HIT_SPEED = 1400;
	static constexpr float SPEED_UP = 1.05;

	sf::Vector2f m_Velocity;
	World* m_World = nullptr;
	float m_Speed = 0;
	bool m_FirstHit = true;

	void normalize();

	void reset();

	void initializeVelocity();

	void handleBorderCollisions();

	void checkForScores(Hud&);

public:
	Ball() = default;

	Ball(const sf::Vector2f&, World&);

	void init(const sf::Vector2f&, World&);

	void update(const sf::Time&, Hud&);

	void setVelocity(float, float);

	sf::Vector2f getVelocity() const;

	float getSpeed() const;
};