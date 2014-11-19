#include "TileMap.hpp"


TileMap::TileMap(sf::Vector2u size)
	:mWindowSize(size)
{
	this->CreateLevel();

}


TileMap::~TileMap()
{



}

void
TileMap::CreateLevel()
{
	const int level[] =
	{
		2, 2, 2, 2, 2, 0, 0, 2,
		2, 0, 1, 0, 0, 1, 0, 2,
		2, 0, 0, 0, 2, 0, 0, 2,
		2, 0, 0, 0, 0, 2, 0, 2,
		2, 0, 0, 1, 0, 0, 0, 2,
		2, 0, 2, 0, 0, 0, 1, 2,
		2, 0, 1, 0, 2, 0, 0, 2,
		2, 0, 0, 0, 0, 1, 0, 2,
		2, 0, 0, 0, 0, 0, 2, 2,
		2, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 2, 1, 0, 0, 2,
		2, 0, 1, 0, 0, 2, 1, 2,
		2, 2, 2, 2, 2, 2, 2, 2,
	};



	unsigned int height = 13;
	unsigned int width = 8;
	unsigned int heightPos = 0;
	unsigned int widthPos = 0;
	float texturePosX = 0;
	float texutePosY = 0;
	float textureSize = 80;
	for (unsigned int i = 0; i < height; ++i)
	{
		for (unsigned int j = 0; j < width; ++j)
		{
			sf::Sprite tempSprite;

			switch (level[mSpritesToDraw.size()])
			{
			case 0:
				tempSprite = mTextureManager.getRef("Ice1");
				tempSprite.setScale(5.0f, 5.0f);
				tempSprite.setPosition(texturePosX, texutePosY);
				break;
			case 1:
				tempSprite = mTextureManager.getRef("Ice2");
				tempSprite.setScale(5.0f, 5.0f);
				tempSprite.setPosition(texturePosX, texutePosY);
				break;
			case 2:
				tempSprite = mTextureManager.getRef("Wall1");
				tempSprite.setScale(5.0f, 5.0f);
				tempSprite.setPosition(texturePosX, texutePosY);
				mCollisionSprites.push_back(tempSprite);
				break;

			default:
				break;
			}
			mSpritesToDraw.push_back(tempSprite);
			texturePosX += 80;
		}
		texturePosX = 0;
		texutePosY += textureSize;
	}
}



void 
TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	for (unsigned int i = 0; i < mSpritesToDraw.size(); ++i)
	{
		target.draw(mSpritesToDraw[i]);
	}

}


std::vector<sf::Sprite>
TileMap::getCollisionSprites() const
{
	return this->mCollisionSprites;
}