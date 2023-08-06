#pragma once

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

class Hud;

// A World class where all the game entities live
class World
{
public:
	World() = default;

	void init();

	void process(const sf::Event);

	void update(const sf::Time&, Hud&);

	void render(sf::RenderWindow&);

	void resetPaddles();

	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;
};

