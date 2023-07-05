#include <cstdlib>
#include <cmath>
#include <iostream>

#include "World.h"
#include "Paddle.h"
#include "Ball.h"
#include "Constants.h"
#include "Hud.h"

// Constructors / Destructors

Ball::Ball(const sf::Vector2f& size, World& world)
: sf::RectangleShape(size), m_Speed(INIT_SPEED), m_World(&world)
{
	initializeVelocity();
}

// Public Methods

void Ball::init(const sf::Vector2f& size, World& world)
{
	setSize(size);
	m_Speed = INIT_SPEED;
	m_World = &world;
	initializeVelocity();
}

void Ball::update(const sf::Time& dt, Hud& hud)
{
	move(m_Velocity * m_Speed * dt.asSeconds());
	handleBorderCollisions();
	checkForScores(hud);
}

// Setters / Getters

void Ball::setVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
	normalize();
	
	if (m_FirstHit)
	{
		m_Speed = HIT_SPEED;
		m_FirstHit = false;
	}
	else
	{
		m_Speed *= SPEED_UP;
	}
}

sf::Vector2f Ball::getVelocity()
{
	return m_Velocity;
}

// Private Methods

void Ball::normalize()
{
	float magnitude_squared = std::pow(m_Velocity.x, 2) + std::pow(m_Velocity.y, 2);
	float magnitude = std::sqrt(magnitude_squared);

	m_Velocity.x /= magnitude;
	m_Velocity.y /= magnitude;
}

void Ball::reset()
{
	setPosition(
		VIRTUAL_SIZE.x / 2 - getSize().x / 2,
		VIRTUAL_SIZE.y / 2 - getSize().y / 2
	);
	initializeVelocity();

	m_FirstHit = true;
	m_Speed = INIT_SPEED;
}

void Ball::initializeVelocity()
{
	m_Velocity.x = -1 + rand() / ((float) RAND_MAX / 2);

	float tmp_y = rand() / ((float) RAND_MAX / (m_Velocity.x * 2));
	m_Velocity.y = rand() % 2 == 0 ? tmp_y : -tmp_y;

	normalize();
}

void Ball::handleBorderCollisions()
{
	sf::Vector2f pos = getPosition();
	
	if (pos.y < BORDER_OUTLINE)
	{
		m_Velocity.y *= -1;
		setPosition(pos.x, BORDER_OUTLINE);
	}
	else if (pos.y + getSize().y > VIRTUAL_SIZE.y - BORDER_OUTLINE)
	{
		m_Velocity.y *= -1;
		setPosition(pos.x, VIRTUAL_SIZE.y - BORDER_OUTLINE - getSize().y);
	}
}

void Ball::checkForScores(Hud& hud)
{
	sf::Vector2f pos = getPosition();

	if (pos.x + getSize().x < 0)
	{
		hud.incrementScore(Paddle::Side::RIGHT);
		reset();
	}
	else if (pos.x > VIRTUAL_SIZE.x)
	{
		hud.incrementScore(Paddle::Side::LEFT);
		reset();
	}
}

