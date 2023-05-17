#include "WallTexture.h"

namespace Engine 
{
	namespace Graphics 
	{ 
		WallTexture::WallTexture(sf::Texture& texture): texture(texture)
		{
			sf::Image image = texture.copyToImage();
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
