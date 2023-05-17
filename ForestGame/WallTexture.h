#pragma once

#include <array>
#include "Configuration.h"

namespace Engine
{
	namespace Graphics 
	{
		using namespace Engine::Config::Graphics;
		using ColorVec = std::array<sf::Color, textureSize>;
		using ColorMatrix = std::array<ColorVec, textureSize>;

		class WallTexture
		{
		private:
			// the image is stored rotated at 90 degrees, because it is easier to work with
			// the render is done horizontally, so getting each column of the texture is more efficient
			ColorMatrix matrix;
			sf::Texture texture;

		public:
			WallTexture(const std::string& fileName);
			const ColorVec& getColumn(int index) const;
			
			const sf::Texture& getTexture();

		};
	}
}

