#include <cstdlib>
#include <cmath>

#include "World.h"
#include "Ball.h"

// Constructors / Destructors

Ball::Ball(const sf::Vector2f& size, float speed, World& world)
: sf::RectangleShape(size), m_Speed(speed), m_World(&world)
{
	initializeVelocity();
}

Ball::~Ball()
{
	delete m_World;
}

// Public Methods

void Ball::init(const sf::Vector2f& size, float speed, World& world)
{
	setSize(size);
	m_Speed = speed;
	m_World = &world;
	initializeVelocity();
}

void Ball::update(const sf::Time& dt)
{
	move(m_Velocity * m_Speed * dt.asSeconds());
	handlePaddleCollisions();
	handleBorderCollisions();
}

// Private Methods

void Ball::normalize()
{
	float magnitude_squared = std::pow(m_Velocity.x, 2) + std::pow(m_Velocity.y, 2);
	float magnitude = std::sqrt(magnitude_squared);

	m_Velocity.x /= magnitude;
	m_Velocity.y /= magnitude;
}

void Ball::initializeVelocity()
{
	m_Velocity.x = -1 + rand() / ((float) RAND_MAX / 2);
	m_Velocity.y = -1 + rand() / ((float) RAND_MAX / 2);
	normalize();
}

void Ball::handlePaddleCollisions()
{
	
}

void Ball::handleBorderCollisions()
{

}

