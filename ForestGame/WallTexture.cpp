#include "WallTexture.h"

namespace Engine 
{
	namespace Graphics 
	{ 
		WallTexture::WallTexture(const std::string& fileName) 
		{
			sf::Image image;
			if (!image.loadFromFile(fileName))
				throw std::runtime_error("Image file doesn't exist");
			if (image.getSize() != sf::Vector2u{ textureSize, textureSize })
				throw std::runtime_error("Invalid image size");
			texture.loadFromImage(image);
			for (int i = 0; i < textureSize; i++)
			{
				sf::Texture column;
				column.loadFromImage(image, { i, 0, 1, textureSize });
				columns[i] = column;
			}
		}

		const sf::Texture& WallTexture::getColumn(int index) const
		{
			return columns[index];
		}


		const sf::Texture& WallTexture::getTexture()
		{
			return texture;
		}
	}
}
