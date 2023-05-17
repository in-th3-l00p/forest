#pragma once

#include <set>
#include <SFML/Graphics.hpp>
#include "Scenes.h"

namespace Engine 
{
	class Game
	{
	private:
		sf::RenderWindow window;
		Scenes::Scene* currentScene;
	
	public:
		Game();
		~Game() = default;

		void run(); // game loop
	};
}
