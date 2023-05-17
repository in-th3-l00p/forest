#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace Engine
{
	namespace Logics
	{
		struct Entity
		{
			sf::Vector3f position;
			const sf::Texture& texture;
			float radius;

			virtual void update(float& deltaTime) = 0;

			Entity() = default;
			Entity(const sf::Texture& texture, sf::Vector3f position, float radius);
		};

		struct StaticEntity: public Entity
		{
		public:
			StaticEntity(const sf::Texture& texture, sf::Vector3f position, float radius);
			void update(float& deltaTime) {}
		};
	}
}

