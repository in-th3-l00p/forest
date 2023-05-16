#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace Engine {
	struct Cell {

	};

	class Map
	{
	private:
		std::vector<std::vector<bool>> matrix;
		float cellSize; // the size of a cell with virtual units

	public:
		Map();
		void renderMinimap(sf::RenderWindow& window, float cellSize);
	};
}
