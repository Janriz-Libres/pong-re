#pragma once

#include <SFML/Graphics.hpp>

class Ball;
class World;

struct Keys
{
	sf::Keyboard::Key up_key, down_key;
};

class Paddle : public sf::RectangleShape
{
public:
	enum Side { LEFT, RIGHT };
	static constexpr float GUTTER = 120;
	static constexpr float V_GAP = 200;

private:
	static constexpr float WIDTH = 40;
	static constexpr float HEIGHT = 250;
	static constexpr float P_SPEED = 1500;

	Side m_Side = LEFT;
	Keys m_Keys;
	World* m_World = nullptr;

	bool m_PressedUp = false;
	bool m_PressedDown = false;

public:
	Paddle() = default;

	Paddle(const Side&, World&);

	void init(const Side&, World&);

	void process(const sf::Event event);

	void update(const sf::Time&);

private:
	void initializeKeys();

	void updateControllable(const sf::Time&);

	void updateRightPaddle(const sf::Time&);

	void handleBoundaries();

	void handleBallCollisions();

	void handleSideCollisions(Ball& ball);

	bool hasCollidedWithBall();
};

