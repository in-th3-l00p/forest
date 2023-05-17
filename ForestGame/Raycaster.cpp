#include <cmath>
#include <iostream>
#include "Raycaster.h"

namespace Engine
{
	namespace Logics
	{
		Raycaster::Intersection Raycaster::verticalRaycast(float& angle) const
		{
			if (angle == RAD90 || angle == RAD270)
				return Intersection();

			sf::Vector2i playerCell(std::floor(
				player.position.x / map.getWallSize()),
				std::floor(player.position.y / map.getWallSize()
				));
			bool east = true;
			sf::Vector2f firstDistance;
			if (angle < RAD90 || angle > RAD270)
				firstDistance.x = (playerCell.x + 1)* map.getWallSize() - player.position.x;
			else {
				firstDistance.x = playerCell.x * map.getWallSize() - player.position.x;
				east = false;
			}
			firstDistance.y = firstDistance.x * std::tan(angle);
			
			sf::Vector2f delta;
			delta.x = map.getWallSize() * (east ? 1 : -1);
			delta.y = delta.x * std::tan(angle);
			Intersection intersection = runDDA(firstDistance, delta, angle, (east ? 1 : -1), 0);
			intersection.horizontal = false;
			return intersection;
		}

		Raycaster::Intersection Raycaster::horizontalRaycast(float& angle) const
		{
			if (angle == 0 || angle == RAD180)
				return Intersection();

			// find the first intersection with a horizontal line
			sf::Vector2i playerCell(std::floor(
				player.position.x / map.getWallSize()),
				std::floor(player.position.y / map.getWallSize()
				));
			bool south = true;
			sf::Vector2f firstDistance;
			if (angle < RAD180 && angle > 0)
				firstDistance.y = (playerCell.y + 1)* map.getWallSize() - player.position.y;
			else {
				firstDistance.y = playerCell.y * map.getWallSize() - player.position.y;
				south = false;
			}
			firstDistance.x = firstDistance.y * (1 / std::tan(angle));

			sf::Vector2f delta;
			delta.y = map.getWallSize() * (south ? 1 : -1);
			delta.x = delta.y * (1 / std::tan(angle));
			return runDDA(firstDistance, delta, angle, 0, (south ? 1 : -1));
		}

		Raycaster::Intersection Raycaster::runDDA(
			sf::Vector2f& firstDistance, 
			sf::Vector2f& delta, 
			float& angle, 
			float offsetX, float offsetY
		) const
		{
			Intersection intersection;
			sf::Vector2f coordinate = player.position + firstDistance;
			sf::Vector2i cell = { 
				static_cast<int>((coordinate.x + offsetX) / map.getWallSize()), 
				static_cast<int>((coordinate.y + offsetY) / map.getWallSize())
			};
			double distance = (
				(coordinate.x - player.position.x) * (coordinate.x - player.position.x) +
				(coordinate.y - player.position.y) * (coordinate.y - player.position.y)
				);
			while (
				cell.x >= 0 && cell.x < map.getMatrix()[0].size() && 
				cell.y >= 0 && cell.y < map.getMatrix().size() &&
				distance < Config::Graphics::Raycaster::renderDistanceSquare
				) 
			{
				if (!map.getMatrix()[cell.y][cell.x].empty)
				{
					intersection.cell = &(map.getMatrix()[cell.y][cell.x]);
					intersection.cellCoordinate = { cell.x, cell.y };
					intersection.point = coordinate;
					intersection.distance = std::sqrt(distance);
					intersection.angle = angle;
					break;
				}
				coordinate += delta;
				cell = {
					static_cast<int>((coordinate.x + offsetX) / map.getWallSize()), 
					static_cast<int>((coordinate.y + offsetY) / map.getWallSize())
				};
				distance = (
					(coordinate.x - player.position.x) * (coordinate.x - player.position.x) +
					(coordinate.y - player.position.y) * (coordinate.y - player.position.y)
					);
			}

			return intersection;
		}

		Raycaster::Intersection Raycaster::raycast(float& angle) const
		{
			Intersection horizontal = horizontalRaycast(angle);
			Intersection vertical = verticalRaycast(angle);
			if (!horizontal.cell && !vertical.cell)
				return horizontal;
			if (!horizontal.cell)
				return vertical;
			if (!vertical.cell)
				return horizontal;
			if (horizontal.distance < vertical.distance)
				return horizontal;
			return vertical;
		}

		Raycaster::Raycaster(Player& player, Map& map)
			: player(player), map(map)
		{
		}

		void Raycaster::render(sf::RenderWindow& window) const
		{
			// debug only, draw the lines on the minimap
			float cellSize = 60;
			float ratio = cellSize / 32.0;

			sf::Vector2f startPosition{
				window.getSize().x / 2 - (cellSize * map.getMatrix()[0].size()) / 2,
				window.getSize().y / 2 - (cellSize * map.getMatrix().size()) / 2
			};

			sf::Sprite lineSprite;
			float lineWidth = window.getSize().x / Config::Graphics::Raycaster::lineCount;
			int currentLine = 0;
			for (
				float angleLoop = player.angle - Config::Graphics::Raycaster::fieldOfView / 2;
				angleLoop < player.angle + Config::Graphics::Raycaster::fieldOfView / 2;
				angleLoop += Config::Graphics::Raycaster::raycastStep, currentLine++
				)
			{
				float angle = angleLoop;
				if (angle < 0)
					angle += RAD360;
				else if (angle >= RAD360)
					angle -= RAD360;
				Intersection intersection = raycast(angle);
				if (!intersection.cell)
					continue;

				// used for fixing the fisheye effect
				float ratio = std::cos(angle - player.angle);
				float lineHeight =
					(
						static_cast<float>(window.getSize().y) /
						(intersection.distance * Config::Graphics::Raycaster::distanceMultiplier * ratio)
						) * Config::Graphics::Raycaster::lineMultiplier;
				float pixelHeight = lineHeight / Config::Graphics::textureSize;
				lineSprite.setTexture(intersection.cell->textures[0].getColumn(0));
				lineSprite.setScale(lineWidth, lineHeight / Config::Graphics::textureSize);
				lineSprite.setPosition(
					currentLine * lineWidth, 
					window.getSize().y / 2 - lineHeight / 2
				);
				if (intersection.horizontal)
					lineSprite.setColor(sf::Color(200, 200, 200));
				else
					lineSprite.setColor(sf::Color(255, 255, 255));
				window.draw(lineSprite);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				map.renderMinimap(window, player);
		}
	}
}
