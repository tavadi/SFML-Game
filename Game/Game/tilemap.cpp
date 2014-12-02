#include "TileMap.hpp"

TileMap::TileMap(sf::Vector2u size)
	:mWindowSize(size)
	, mMapHeight(200)
	, mMapWidth(8)
	, mTexturePosX(0)
	, mTexturePosY(5000)
	, mTexuteSize(size.x/mMapWidth)
	, mapCount(mMapHeight*mMapWidth)
	, mLevel(new int[mapCount])
	, noCollisionCount(1)
{
	this->populateArr(mLevel);
	this->CreateLevel();
}


TileMap::~TileMap()
{
	delete[] mLevel;
}


void 
TileMap::populateArr(int* level)
{
	
	for (int i = 0; i < mapCount; ++i)
	{
		
		if (i % mMapWidth == 0 || i % mMapWidth == 7)
		{
			level[i] = 2;
		}
		else
		{
			int random = rand() % 4;
			if (noCollisionCount % 3 + random == 0 || noCollisionCount % 1 + random == 0)
			{
				level[i] = 2;
				noCollisionCount++;
			}
			else
			{
				
				level[i] = 1;
				noCollisionCount++;
			}
		}
	}
}

void
TileMap::CreateLevel()
{



	 for (unsigned int i = 0; i < mMapHeight; ++i)
	 {
		 for (unsigned int j = 0; j < mMapWidth; ++j)
		 {
			 Tile tempSprite;
			 switch (mLevel[mSpritesToDraw.size()])
			 {

			 case 0:
				 tempSprite.setSprite(mTextureManager.getRef("Ice1"));
				 tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				 tempSprite.setTileType("Ice");
				 tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				 break;
			 case 1:
				 tempSprite.setSprite(mTextureManager.getRef("Ice2"));
				 tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				 tempSprite.setTileType("Ice");
				 tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				 break;
			 case 2:
				 tempSprite.setSprite(mTextureManager.getRef("Wall1"));
				 tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				 tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				 tempSprite.setTileType("Wall");
				 mCollisionSprites.push_back(tempSprite);
				 break;

			 default:
				 break;
			 }
			 mSpritesToDraw.push_back(tempSprite);
			 mTexturePosX += mTexuteSize;
		 }
		 mTexturePosX = 0;
		 mTexturePosY -= mTexuteSize;
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
		
		target.draw(mSpritesToDraw[i].getSpriteToDraw());
	}

}


std::vector<Tile>&
TileMap::getCollisionSprites() 
{
	return this->mCollisionSprites;
}