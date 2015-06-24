#include <SFML/Graphics.hpp>
#include "World1.h"
#include <iostream>

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const float MS_PER_UPDATE = 14.00f;
	//const double MS_PER_UPDATE = 8.33333333333;
	//const double MS_PER_UPDATE = 33.3333333333;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Battle");
	sf::View view;
	// Initialise view
	view.reset(sf::FloatRect(0.00f, 0.00f, 800.00f, 600.00f));
	window.setView(view);
	IWorld* world = new World1();
	world->create();
	sf::Clock loop_clock;
	sf::Clock clock;
	sf::Time previous = clock.restart();
	double lag = 0.0;
	loop_clock.restart();

	while (window.isOpen())
	{
		sf::Time loop_time = loop_clock.restart();
		//std::cout << loop_time.asMicroseconds() << "\n";
		sf::Time current = clock.getElapsedTime();
		double elapsed = current.asMilliseconds() - previous.asMilliseconds();
		previous = current;
		lag += elapsed;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		// Input
		world->input();
		// Update
		while (lag >= MS_PER_UPDATE)
		{
			world->update();
			lag -= MS_PER_UPDATE;
		}

		// Draw
		window.clear(sf::Color(25, 25, 25, 255));
		world->draw(window, lag / MS_PER_UPDATE);
		//world->draw(window, 1);
		window.display();
	}
	world->cleanup();
	delete world;
	return 0;
}