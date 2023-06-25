#pragma once

#include <SFML/Graphics.hpp>

class World;

struct Keys
{
	sf::Keyboard::Key up_key, down_key;
};

class Paddle : public sf::RectangleShape
{
public:
	enum Side { LEFT, RIGHT };

private:
	Side m_Side = LEFT;
	World* m_World = nullptr;

	void copy(const Paddle&);

	void updateControllable(const sf::Time&, const Keys&);

	void updateRightPaddle(const sf::Time&);

	void handleBoundaries();

	void handleBallCollisions();

	bool hasCollidedWithBall();

public:
	Paddle() = default;

	Paddle(const sf::Vector2f&, const Side&, World&);

	Paddle(const Paddle&);

	~Paddle();

	Paddle& operator=(const Paddle&);

	void init(const sf::Vector2f&, const Side&, World&);

	void update(const sf::Time&);
};

