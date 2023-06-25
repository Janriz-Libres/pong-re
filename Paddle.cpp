#include "World.h"
#include "Paddle.h"

// Constructors / Destructors

Paddle::Paddle(const sf::Vector2f& size, const Side& side, World& world)
: sf::RectangleShape(size), m_Side(side), m_World(&world) {}

Paddle::Paddle(const Paddle& other)
{
	copy(other);
}

Paddle::~Paddle()
{
	delete m_World;
}

// Public Methods

Paddle& Paddle::operator=(const Paddle& other)
{
	copy(other);
	return *this;
}

void Paddle::init(const sf::Vector2f& size, const Side& side, World& world)
{
	setSize(size);
	m_Side = side;
	m_World = &world;
}

void Paddle::update(const sf::Time& dt)
{
	switch (m_Side) {
		case LEFT:
			updateControllable(dt, Keys{sf::Keyboard::W, sf::Keyboard::S});
			break;
		case RIGHT:
			updateRightPaddle(dt);
	}

	handleBoundaries();
	handleBallCollisions();
}

// Private Methods

void Paddle::copy(const Paddle& other)
{
	m_Side = other.m_Side;

	delete m_World;
	m_World = new World;
	*m_World = *other.m_World;
}

void Paddle::updateControllable(const sf::Time& dt, const Keys& keys)
{
	float dir = 0;

	if (sf::Keyboard::isKeyPressed(keys.up_key)) dir -= 1;
	if (sf::Keyboard::isKeyPressed(keys.down_key)) dir += 1;

	move(0, dir * P_SPEED * dt.asSeconds());
}

void Paddle::updateRightPaddle(const sf::Time& dt)
{
	updateControllable(dt, Keys{sf::Keyboard::Up, sf::Keyboard::Down});
}

void Paddle::handleBoundaries()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = getSize();

	if (pos.y < 0) setPosition(pos.x, 0);
	if (pos.y + size.y > VIRTUAL_SIZE.y) setPosition(pos.x, VIRTUAL_SIZE.y - size.y);
}

void Paddle::handleBallCollisions()
{
	if (!hasCollidedWithBall()) return;

	sf::Vector2f ball_pos = m_World->m_Ball.getPosition();
	sf::Vector2f ball_size = m_World->m_Ball.getSize();

	sf::Vector2f self_pos = getPosition();
	sf::Vector2f self_size = getSize();

	// Modify ball speed/direction based on collision
	float self_x_center = self_pos.x + self_size.x / 2;
	float ball_x_center = ball_pos.x + ball_size.x / 2;

	if (ball_pos.y < self_pos.y || ball_pos.y + ball_size.y > self_pos.y + self_size.y)
	{
		// TODO
	}
	else
	{
		m_World->m_Ball.setVelocityByInversion(true, false);
	}
}

bool Paddle::hasCollidedWithBall()
{
	sf::Vector2f ball_pos = m_World->m_Ball.getPosition();
	sf::Vector2f ball_size = m_World->m_Ball.getSize();

	sf::Vector2f self_pos = getPosition();
	sf::Vector2f self_size = getSize();

	if (ball_pos.x > self_pos.x + self_size.x) return false;
	if (ball_pos.x + ball_size.x < self_pos.x) return false;
	if (ball_pos.y + ball_size.y < self_pos.y) return false;
	if (ball_pos.y > self_pos.y + self_size.y) return false;

	return true;
}

