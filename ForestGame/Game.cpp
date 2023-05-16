#include "Game.h"
#include "Configuration.h"

Engine::Game::Game()
	: window(Config::Window::size, Config::Window::title)
{
}

void Engine::Game::run()
{
	while (window.isOpen()) {
		sf::Event event; // event driven programming go brttttt
		while (window.pollEvent(event))
			switch (event.type) 
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				sf::FloatRect view(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(view));
				break;
			}
		window.clear();

		window.display();
	}
}
