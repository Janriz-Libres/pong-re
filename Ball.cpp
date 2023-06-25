#include <cstdlib>
#include <cmath>

#include "World.h"
#include "Ball.h"
#include "Constants.h"

// Constructors / Destructors

Ball::Ball(const sf::Vector2f& size, float speed, World& world)
: sf::RectangleShape(size), m_Speed(speed), m_World(&world)
{
	initializeVelocity();
}

Ball::Ball(const Ball& other)
{
	copy(other);
}

Ball::~Ball()
{
	delete m_World;
}

// Public Methods

Ball& Ball::operator=(const Ball& other)
{
	copy(other);
	return *this;
}

void Ball::init(const sf::Vector2f& size, float speed, World& world)
{
	setSize(size);
	m_Speed = speed;
	m_World = &world;
	initializeVelocity();
}

void Ball::setVelocityByInversion(bool invertX, bool invertY)
{
	m_Velocity.x *= invertX ? -1 : 1;
	m_Velocity.y *= invertY ? -1 : 1;
}

void Ball::update(const sf::Time& dt)
{
	move(m_Velocity * m_Speed * dt.asSeconds());
	handleBorderCollisions();
}

// Private Methods

void Ball::copy(const Ball& other)
{
	m_Speed = other.m_Speed;
	m_Velocity = other.m_Velocity;

	delete m_World;
	m_World = new World;
	*m_World = *other.m_World;
}

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

void Ball::handleBorderCollisions()
{
	sf::Vector2f pos = getPosition();
	if (pos.y < 0 || pos.y + getSize().y > VIRTUAL_SIZE.y) m_Velocity.y *= -1;
}

