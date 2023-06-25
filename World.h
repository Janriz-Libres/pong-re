#pragma once

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Constants.h"

class World
{
public:
	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;
	
	World() = default;

	void init()
	{
		m_LeftPaddle.init(PADDLE_SIZE, Paddle::Side::LEFT, *this);
		m_LeftPaddle.setPosition(GUTTER, VIRTUAL_SIZE.y - m_LeftPaddle.getSize().y - V_GAP);

		m_RightPaddle.init(PADDLE_SIZE, Paddle::Side::RIGHT, *this);
		m_RightPaddle.setPosition(VIRTUAL_SIZE.x - GUTTER - m_RightPaddle.getSize().x, V_GAP);

		m_Ball.init(sf::Vector2f(40, 40), 700, *this);
		m_Ball.setPosition(
			VIRTUAL_SIZE.x / 2 - m_Ball.getSize().x / 2,
			VIRTUAL_SIZE.y / 2 - m_Ball.getSize().y / 2
		);
	}

	void update(const sf::Time& dt)
	{
		m_LeftPaddle.update(dt);
		m_RightPaddle.update(dt);
		m_Ball.update(dt);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(m_LeftPaddle);
		window.draw(m_RightPaddle);
		window.draw(m_Ball);
	}
};

