#include "WallTexture.h"

namespace Engine 
{
	namespace Graphics 
	{ 
		WallTexture::WallTexture(const std::string& fileName) 
		{
			if (!texture.loadFromFile(fileName))
				throw std::runtime_error("Image file doesn't exist");
			if (texture.getSize() != sf::Vector2u{ textureSize, textureSize })
				throw std::runtime_error("Invalid image size");
			sf::Image image = texture.copyToImage();
			for (int i = 0; i < textureSize; i++)
				for (int j = 0; j < textureSize; j++)
					matrix[j][i] = image.getPixel(i, j);
		}

		const ColorVec& WallTexture::getColumn(int index) const
		{
			return matrix[index];
		}


		const sf::Texture& WallTexture::getTexture()
		{
			return texture;
		}
	}
}
