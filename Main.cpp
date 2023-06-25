#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "GameView.h"
#include "World.h"

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
	border.setOutlineThickness(-20);

	World world;
	world.init();

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
		}

		world.update(dt);

		window.clear();

		window.draw(border);
		world.render(window);

		window.display();
	}
	
	return 0;
}