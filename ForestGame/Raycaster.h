#pragma once

#include <set>
#include <utility>
#include <map>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Entity.h"

namespace Engine 
{
	namespace Logics
	{
		class Raycaster
		{
		private:
			struct Intersection
			{
				const Cell* cell = nullptr;
				sf::Vector2i cellCoordinate;
				sf::Vector2f point;
				float distance, angle;
				bool horizontal = true;
			};

			Player& player;
			Map& map;
			std::vector<Entity*>& entities;
			mutable std::vector<float> zBuffer;

			static float mapInterval(float x, float inMin, float inMax, float outMin, float outMax);
			static sf::Color depthColor(float distance);
			static void horizontalDarken(sf::Color& color);

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
			Raycaster(Player& player, Map& map, std::vector<Entity*>& entities);
			void render(sf::RenderWindow& window) const;
		};
	}
}

