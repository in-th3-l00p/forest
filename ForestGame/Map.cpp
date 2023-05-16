#include "Map.h"

Engine::Map::Map()
{
	matrix = {
		{true, true, true, true},
		{true, false, false, true},
		{true, false, false, true},
		{true, true, true, true}
	};
}

void Engine::Map::renderMinimap(sf::RenderWindow& window, float cellSize)
{
	for (int y = 0; y < matrix.size(); y++)
		for (int x = 0; x < matrix[y].size(); x++) {
			sf::RectangleShape rectangle({cellSize, cellSize});
			rectangle.setPosition({ x * cellSize, y * cellSize });
			if (matrix[y][x])
				rectangle.setFillColor(sf::Color::White);
			else
				rectangle.setFillColor(sf::Color::Black);
			window.draw(rectangle);
		}
}
