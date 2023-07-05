#include <cmath>

#include "World.h"
#include "Paddle.h"
#include "Ball.h"
#include "Constants.h"

// Constructors / Destructors

Paddle::Paddle(const Side& side, World& world)
: sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT)), m_Side(side), m_World(&world)
{
	initializeKeys();
}

// Public Methods

void Paddle::init(const Side& side, World& world)
{
	setSize(sf::Vector2f(WIDTH, HEIGHT));
	m_Side = side;
	m_World = &world;
	initializeKeys();
}

void Paddle::process(const sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == m_Keys.up_key) m_PressedUp = true;
		if (event.key.code == m_Keys.down_key) m_PressedDown = true;
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == m_Keys.up_key) m_PressedUp = false;
		if (event.key.code == m_Keys.down_key) m_PressedDown = false;
	}
}

void Paddle::update(const sf::Time& dt)
{
	switch (m_Side) {
		case LEFT:
			updateControllable(dt);
			break;
		case RIGHT:
			updateRightPaddle(dt);
	}

	handleBoundaries();
	handleBallCollisions();
}

// Private Methods

void Paddle::initializeKeys()
{
	if (m_Side == Paddle::Side::LEFT)
		m_Keys = {sf::Keyboard::W, sf::Keyboard::S};
	else
		m_Keys = {sf::Keyboard::Up, sf::Keyboard::Down};
}

void Paddle::updateControllable(const sf::Time& dt)
{
	float dir = 0;

	if (m_PressedUp) dir -= 1;
	if (m_PressedDown) dir += 1;

	move(0, dir * P_SPEED * dt.asSeconds());
}

void Paddle::updateRightPaddle(const sf::Time& dt)
{
	updateControllable(dt);
}

void Paddle::handleBoundaries()
{
	const sf::Vector2f pos = getPosition();
	const sf::Vector2f size = getSize();

	if (pos.y < BORDER_OUTLINE) setPosition(pos.x, 0);
	if (pos.y + size.y > VIRTUAL_SIZE.y - BORDER_OUTLINE) setPosition(pos.x, VIRTUAL_SIZE.y - size.y);
}

void Paddle::handleBallCollisions()
{
	if (!hasCollidedWithBall()) return;

	Ball& ball = m_World->m_Ball;

	const sf::Vector2f self_pos = getPosition();
	const sf::Vector2f ball_vel = ball.getVelocity();

	const float ball_y_center = ball.getPosition().y + ball.getSize().y / 2;

	// Modify ball speed/direction based on point of collision
	if (ball_y_center < self_pos.y) // When ball hit the top of the paddle
	{
		ball.setVelocity(-ball_vel.x, ball_vel.y < 0 ? ball_vel.y : -ball_vel.y);
	}
	else if (ball_y_center > self_pos.y + getSize().y) // Ball hit bottom of paddle
	{
		ball.setVelocity(-ball_vel.x, ball_vel.y < 0 ? -ball_vel.y : ball_vel.y);
	}
	else // Ball hit either side of the paddle
	{
		handleSideCollisions(ball);
	}
}

void Paddle::handleSideCollisions(Ball& ball)
{
	const sf::Vector2f self_pos = getPosition();
	const sf::Vector2f self_size = getSize();

	const sf::Vector2f ball_pos = ball.getPosition();
	const sf::Vector2f ball_size = ball.getSize();

	const sf::Vector2f ball_vel = ball.getVelocity();

	const float self_x_center = self_pos.x + self_size.x / 2;
	const float ball_x_center = ball_pos.x + ball_size.x / 2;
	const float ball_y_center = ball_pos.y + ball_size.y / 2;

	const float center = self_size.y / 2;
	const float degree = std::abs(center - (ball_y_center - self_pos.y));
	const float new_vel_y = degree / center * (std::abs(ball_vel.x) * 1.25);

	bool isMoving = m_PressedUp && !m_PressedDown || !m_PressedUp && m_PressedDown;

	if (isMoving)
	{
		ball.setVelocity(-ball_vel.x, m_PressedUp ? -new_vel_y : new_vel_y);
	}
	else
	{
		const float self_y_center = self_pos.y + self_size.y / 2;
		ball.setVelocity(-ball_vel.x, ball_y_center <= self_y_center ? -new_vel_y : new_vel_y);
	}

	ball.setPosition(
		self_pos.x + ((ball_x_center > self_x_center) ? ball_size.x : -ball_size.x),
		ball_pos.y
	);
}

bool Paddle::hasCollidedWithBall()
{
	sf::Vector2f ball_pos = m_World->m_Ball.getPosition();
	sf::Vector2f ball_size = m_World->m_Ball.getSize();

	sf::Vector2f self_pos = getPosition();
	sf::Vector2f self_size = getSize();

	if (ball_pos.x >= self_pos.x + self_size.x) return false;
	if (ball_pos.x + ball_size.x <= self_pos.x) return false;
	if (ball_pos.y + ball_size.y <= self_pos.y) return false;
	if (ball_pos.y >= self_pos.y + self_size.y) return false;

	return true;
}

