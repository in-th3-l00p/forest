#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "WallTexture.h"
#include "Player.h"

namespace Engine {
	namespace Logics
	{
		struct Cell
		{
			bool empty;
			std::vector<Graphics::WallTexture> textures;
			int animationInterval;
		};

		class Map
		{
		private:
			std::vector<std::vector<Cell>> matrix;
			float wallSize = 32; // the size of a cell with virtual units

		public:
			Map();
			void renderMinimap(
				sf::RenderWindow& window, 
				Logics::Player& player,
				float cellSize = 60
			);

			const std::vector<std::vector<Cell>>& getMatrix() const;
			const float& getWallSize() const;
		};
	}
}
