#pragma once

#include <SFML/Graphics.hpp>

// Game State
enum State { MENU, PLAY, PAUSED, SCORED, GAME_OVER };
inline State state = MENU;

enum Mode { SINGLE, DOUBLE };
inline Mode mode = SINGLE;

// Define global constants
const sf::Vector2u VIRTUAL_SIZE(2880, 2160); // 4:3 aspect ratio (4K UHD)
const sf::VideoMode RESOLUTION = sf::VideoMode::getDesktopMode();
const float BORDER_OUTLINE = 20;

