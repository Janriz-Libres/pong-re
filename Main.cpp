#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "GameView.h"
#include "World.h"
#include "Hud.h"

int main()
{
	std::srand(std::time(0));

	sf::RenderWindow window(sf::VideoMode(RESOLUTION.width - 100, RESOLUTION.height - 100), "Pong");
	window.setVerticalSyncEnabled(true);

	// Center the window
	window.setPosition(sf::Vector2i((RESOLUTION.width - window.getSize().x) / 2, 0));

	GameView game_view(VIRTUAL_SIZE, window.getSize());
	window.setView(game_view);

	// Define border of the game
	sf::RectangleShape border(sf::Vector2f(VIRTUAL_SIZE.x, VIRTUAL_SIZE.y));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(-BORDER_OUTLINE);

	// Define boundary
	sf::RectangleShape b_lines[14];
	for (std::size_t i = 0; i < 14; i++)
	{
		b_lines[i].setSize(sf::Vector2f(BORDER_OUTLINE, 80));
		b_lines[i].setPosition(
			VIRTUAL_SIZE.x / 2 - BORDER_OUTLINE / 2, BORDER_OUTLINE + 155 * i
		);
		b_lines[i].setSize(sf::Vector2f(BORDER_OUTLINE, 80));
	}

	World world;
	world.init();

	Hud hud("PressStart2P.ttf");
	if (!hud.isLoaded()) return -1;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::Resized)
			{
				game_view.adjustView(event.size);
				window.setView(game_view);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					switch (state) {
						case GAME_OVER:
						case MENU:
							state = SCORED;
							hud.resetScores();
							break;
						case PAUSED:
							state = PLAY;
							break;
						case PLAY:
							state = PAUSED;
							break;
					}
				}

				if (event.key.code == sf::Keyboard::Space && state == MENU)
					hud.changeMode();

				if (event.key.code == sf::Keyboard::Escape && state == GAME_OVER)
				{
					state = MENU;
					world.resetPaddles();
				}
			}

			world.process(event);
		}

		world.update(dt, hud);
		hud.update(dt);

		window.clear();

		window.draw(border);

		if (state == PLAY || state == SCORED)
			for (sf::RectangleShape line : b_lines) window.draw(line);

		world.render(window);
		hud.render(window);

		window.display();
	}
	
	return 0;
}