#include "Player.h"

void Engine::Logics::Player::update(float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{
		position.x += direction.x * speed * deltaTime;
		position.y += direction.y * speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position.x -= direction.x * speed * deltaTime;
		position.y -= direction.y * speed * deltaTime;
	}

	int rot = (
		static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) - 
		static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		);
	if (rot)
		setAngle(angle + rotateSpeed * rot * deltaTime);
}

void Engine::Logics::Player::setAngle(float newAngle)
{
	angle = newAngle;
	while (angle < 0)
		angle += RAD360;
	while (angle > RAD360)
		angle -= RAD360;
	direction = { std::cos(angle), std::sin(angle) };
}
