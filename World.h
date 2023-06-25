#pragma once

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Util.h"

class Paddle;
class Ball;

class World
{
private:
	Paddle left_paddle;
	Paddle right_paddle;
	Ball ball;

public:
	World() = default;

	void init()
	{
		left_paddle.init(PADDLE_SIZE, Paddle::Side::LEFT, *this);
		left_paddle.setPosition(GUTTER, VIRTUAL_SIZE.y - left_paddle.getSize().y - V_GAP);

		right_paddle.init(PADDLE_SIZE, Paddle::Side::RIGHT, *this);
		right_paddle.setPosition(VIRTUAL_SIZE.x - GUTTER - right_paddle.getSize().x, V_GAP);

		ball.init(sf::Vector2f(40, 40), 700, *this);
		ball.setPosition(VIRTUAL_SIZE.x / 2 - ball.getSize().x / 2, VIRTUAL_SIZE.y / 2 - ball.getSize().y / 2);
	}

	void update(const sf::Time& dt)
	{
		left_paddle.update(dt);
		right_paddle.update(dt);
		ball.update(dt);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(left_paddle);
		window.draw(right_paddle);
		window.draw(ball);
	}
};