#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define TO_RAD(x) (x * M_PI / 180)
#define TO_DEG(x) (x * 180 / M_PI)

const float RAD90 = M_PI / 2;
const float RAD180 = M_PI;
const float RAD270 = M_PI * 3 / 2;
const float RAD360 = M_PI * 2;

namespace Engine
{
	namespace Config 
	{
		static char executablePath[MAX_PATH];

		namespace Window
		{
			static const sf::VideoMode size{ 1280, 720 };
			static const std::string title = "Forest";
		}

		namespace Graphics {
			static const size_t textureSize = 64;

			namespace Raycaster
			{
				static const float fieldOfView = TO_RAD(45);
				static const float raycastStep = TO_RAD(0.05);
				static const float lineCount = fieldOfView / raycastStep;

				static const float renderDistance = 100;
				static const float renderDistanceSquare = renderDistance * renderDistance;

				static const float lineMultiplier = 40;
				static const float distanceMultiplier = 2;
				static const float horizontalDarkenMultiplier = 0.6;
			}
		}

		namespace Logics
		{
			static const float playerSpeed = 30;
			static const float playerRotateSpeed = TO_RAD(50);
		}

		// singleton that handles loading assets
		class Assets
		{
		public:
			std::string executablePath;
			sf::Font defaultFont;

			sf::Texture brickTexture;
			sf::Texture treeTexture;

		private:
			static Assets* assets;
			Assets();

		public:
			Assets(const Assets& obj) = default;
			static Assets& getAssets();
		};
	}
}
