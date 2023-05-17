#include "Game.h"
#include "Configuration.h"

Engine::Game::Game()
	: window(Config::Window::size, Config::Window::title)
{
	Config::Assets::getAssets();
	//this->currentScene = new Scenes::MainMenu([](Scenes::Scene*) {});
	this->currentScene = new Scenes::RaycasterTest([](Scenes::Scene*) {});
}

void Engine::Game::run()
{
	sf::Clock clock;
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event event; // event driven programming go brttttt
		while (window.pollEvent(event))
			switch (event.type) 
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
					this->currentScene->onClick(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
				break;
			case sf::Event::Resized:
				sf::FloatRect view(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(view));
				this->currentScene->onResize(event.size.width, event.size.height);
				break;
			}

		this->currentScene->update(deltaTime);
		window.clear();
		this->currentScene->render(window);
		window.display();
	}
}
