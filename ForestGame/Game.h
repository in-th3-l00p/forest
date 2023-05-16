#pragma once

#include <set>
#include <SFML/Graphics.hpp>
#include "Node.h"

namespace Engine 
{
	class Game
	{
	private:
		sf::RenderWindow window;
		std::set<Node> nodes;

	public:
		Game();
		~Game() = default;

		void run(); // game loop
	};
}
