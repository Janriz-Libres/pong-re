#pragma once

#include <SFML/Graphics.hpp>

// Define static global constants
const sf::Vector2u VIRTUAL_SIZE(2880, 2160); // 4:3 aspect ratio (4K UHD)
const sf::VideoMode RESOLUTION = sf::VideoMode::getDesktopMode();

// Constants for game actors
const sf::Vector2f PADDLE_SIZE(40, 250);
const float GUTTER = 120;
const float V_GAP = 200;
const float P_SPEED = 1500;

int gcf(int a, int b)
{
	if (a == 0) return b;
	return gcf(b % a, a);
}

