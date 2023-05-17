#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

namespace Engine 
{
	namespace Logics
	{
		class Raycaster
		{
		private:
			Player& player;
			Map& map;

			struct Intersection
			{
				const Cell* cell = nullptr;
				sf::Vector2i cellCoordinate;
				sf::Vector2f point;
				float distance, angle;
				bool horizontal = true;
			};

			Intersection horizontalRaycast(float& angle) const;
			Intersection verticalRaycast(float& angle) const;
			Intersection runDDA(
				sf::Vector2f& firstDistance, 
				sf::Vector2f& delta, 
				float& angle, 
				float offsetX, float offsetY
			) const;
			Intersection raycast(float& angle) const;

		public:
			Raycaster(Player& player, Map& map);
			void render(sf::RenderWindow& window) const;
		};
	}
}

