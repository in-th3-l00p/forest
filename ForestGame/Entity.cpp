#include "Entity.h"

namespace Engine
{
	namespace Logics
	{
		Entity::Entity(const sf::Texture& texture, sf::Vector2f position, float radius)
			: texture(texture)
		{
		}

		StaticEntity::StaticEntity(const sf::Texture& texture, sf::Vector2f position, float radius)
			: Entity(texture, position, radius)
		{
		}
	}
}
