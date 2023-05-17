#include "Map.h"
#include <cmath>

namespace Engine
{
	namespace Logics
	{
		Map::Map()
		{
			Cell texturedCell;
			texturedCell.empty = false;
			texturedCell.textures.push_back(new Graphics::WallTexture(Config::Assets::getAssets().brickTexture));
			Cell emptyCell;
			emptyCell.empty = true;

			matrix = {
				{ texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell },
				{ texturedCell, emptyCell, texturedCell, emptyCell, emptyCell, emptyCell, texturedCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, texturedCell, emptyCell, emptyCell, emptyCell, texturedCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, texturedCell, emptyCell, emptyCell, emptyCell, texturedCell, texturedCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, texturedCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, emptyCell, emptyCell, texturedCell, emptyCell, emptyCell, emptyCell, emptyCell, emptyCell, texturedCell },
				{ texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell, texturedCell }
			};
		}

		void Map::renderMinimap(sf::RenderWindow& window, Player& player, float cellSize)
		{
			sf::Vector2f startPosition{
				window.getSize().x / 2 - (cellSize * matrix[0].size()) / 2,
				window.getSize().y / 2 - (cellSize * matrix[1].size()) / 2
			};

			for (int y = 0; y < matrix.size(); y++)
				for (int x = 0; x < matrix[y].size(); x++) {
					if (!matrix[y][x].empty) {
						sf::Sprite sprite;
						sprite.setTexture(matrix[y][x].textures[0]->getTexture());
						sprite.setPosition(startPosition + sf::Vector2f{ x * cellSize, y * cellSize });
						sprite.setScale({
							cellSize / Engine::Config::Graphics::textureSize,
							cellSize / Engine::Config::Graphics::textureSize }
						);
						window.draw(sprite);
					}
					else {
						sf::RectangleShape rectangle({ cellSize, cellSize });
						rectangle.setPosition(startPosition + sf::Vector2f{ x * cellSize, y * cellSize });
						rectangle.setFillColor(sf::Color::Black);
						window.draw(rectangle);
					}
				}

			float ratio = cellSize / wallSize;
			sf::CircleShape playerCircle(player.radius * ratio);
			playerCircle.setFillColor(sf::Color::Red);
			playerCircle.setOrigin(player.radius * ratio, player.radius * ratio);
			playerCircle.setPosition(startPosition + sf::Vector2f{ player.position.x * ratio, player.position.y * ratio });
			window.draw(playerCircle);

			sf::Vertex direction[] = {
				sf::Vertex(startPosition + sf::Vector2f{ player.position.x * ratio, player.position.y * ratio }),
				sf::Vertex(startPosition + sf::Vector2f{ player.position.x * ratio + player.direction.x * 100, player.position.y * ratio + player.direction.y * 100 })
			};
			direction[0].color = sf::Color::Red;
			direction[1].color = sf::Color::Red;
			sf::VertexArray directionLine(sf::Lines, 2);
			directionLine[0] = direction[0];
			directionLine[1] = direction[1];
			window.draw(directionLine);
		}

		const std::vector<std::vector<Cell>>& Map::getMatrix() const
		{
			return matrix;
		}

		const float& Map::getWallSize() const
		{
			return wallSize;
		}
	}
}
