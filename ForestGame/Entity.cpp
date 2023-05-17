#include "Entity.h"

namespace Engine
{
	namespace Logics
	{
		Entity::Entity(const sf::Texture& texture, sf::Vector3f position, float radius)
			: texture(texture)
		{
			this->position = position;
			this->radius = radius;
		}

		StaticEntity::StaticEntity(const sf::Texture& texture, sf::Vector3f position, float radius)
			: Entity(texture, position, radius)
		{
		}
	}
}
