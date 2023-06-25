#include "World.h"
#include "Paddle.h"

// Constructors / Destructors

Paddle::Paddle(const sf::Vector2f& size, const Side& side, World& world)
: sf::RectangleShape(size), m_Side(side), m_World(&world) {}

Paddle::~Paddle()
{
	delete m_World;
}

// Public Methods

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
}

// Private Methods

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

