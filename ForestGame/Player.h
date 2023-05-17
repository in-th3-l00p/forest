#pragma once

#include <SFML/Graphics.hpp>
#include "Configuration.h"

namespace Engine
{
	namespace Logics
	{
		// player is represented as a circle
		struct Player
		{
			sf::Vector2f position;
			float radius, angle = 0;
			const float speed = Config::Logics::playerSpeed, rotateSpeed = Config::Logics::playerRotateSpeed;
			sf::Vector2f direction = { 1, 0 };

			void update(float& deltaTime);
			void setAngle(float newAngle);
		};
	}
}
