#include "TileMap.hpp"

TileMap::TileMap(sf::Vector2u size)
	:mWindowSize(size)
	, mMapHeight(10)
	, mMapWidth(8)
	, mTexturePosX(0)
	, mTexturePosY(-400)
	, mTexuteSize(80)
	, mapCount(mMapHeight*mMapWidth)
	, mLevel(new int[mapCount])
	, noCollisionCount(1)
	, mapCounter(0)
{
	this->populateArr(mLevel);
	this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel);

	mSpritesToDraw.push_back(mSpritesMap0);

	mCollisionsToHandle.push_back(mCollisionSprites0);
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
			level[i] = 0;
			noCollisionCount++;
		}
	}
}

void
TileMap::createLevel(std::vector<Tile>& Collisionmap, std::vector<Tile>& drawMap, int *level)
{ 
	Collisionmap.clear();
	drawMap.clear();
	 for (unsigned int i = 0; i < mMapHeight; ++i)
	 {
		 for (unsigned int j = 0; j < mMapWidth; ++j)
		 {
			 Tile tempSprite;
			 switch (level[drawMap.size()])
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
				 Collisionmap.push_back(tempSprite);
				 break;

			 default:
				 break;
			 }
			 drawMap.push_back(tempSprite);
			 mTexturePosX += mTexuteSize;
		 }
		 mTexturePosX = 0;
		 mTexturePosY -= mTexuteSize;
	 }
}



void
TileMap::updateTileMap(float camPosY)
{
	//mCamPos = camPosY;
	//
	//if (mCamPos < 800
	//	)
	//	{
	//		std::cout << "Delete: mCollisionSprites [" << mapCounter << "], Create: On top Position  mCollisionSprites[" << mapCounter << "]" << std::endl;
	//		++mapCounter;

	//		switch (mapCounter)
	//		{
	//		case 0:
	//			this->createLevel(mCollisionSprites2, mSpritesMap2, mLevel);
	//			mCollisionsToHandle.clear();
	//			mCollisionsToHandle.push_back(mCollisionSprites1);
	//			mCollisionsToHandle.push_back(mCollisionSprites2);
	//			mSpritesToDraw.clear();
	//			mSpritesToDraw.push_back(mSpritesMap1);
	//			mSpritesToDraw.push_back(mSpritesMap2);
	//			break;
	//		case 1:
	//			this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel);
	//			mCollisionsToHandle.clear();
	//			mCollisionsToHandle.push_back(mCollisionSprites2);
	//			mCollisionsToHandle.push_back(mCollisionSprites0);
	//			mSpritesToDraw.clear();
	//			mSpritesToDraw.push_back(mSpritesMap2);
	//			mSpritesToDraw.push_back(mSpritesMap0);

	//			break;
	//		case 2:
	//			this->createLevel(mCollisionSprites1, mSpritesMap1, mLevel);
	//			mCollisionsToHandle.clear();
	//			mCollisionsToHandle.push_back(mCollisionSprites0);
	//			mCollisionsToHandle.push_back(mCollisionSprites1);
	//			mSpritesToDraw.clear();
	//			mSpritesToDraw.push_back(mSpritesMap0);
	//			mSpritesToDraw.push_back(mSpritesMap1);
	//			break;
	//		case 3:
	//			mapCounter = 0;
	//			break;
	//		}

	////		mTileMapUpdateTime -= sf::seconds(5.0f);
	////	}
	if ((int)camPosY % 800 == 0 && camPosY != 0)
	{
		std::cout << camPosY << std::endl;
		if (mapCounter == 3)
		{
			mapCounter = 0;
		}
		std::cout << "Delete: mCollisionSprites [" << mapCounter << "], Create: On top Position  mCollisionSprites[" << mapCounter << "]" << std::endl;
				switch (mapCounter)
				{
				case 0:
					this->createLevel(mCollisionSprites1, mSpritesMap1, mLevel);
					mCollisionsToHandle.clear();
					mCollisionsToHandle.push_back(mCollisionSprites0);
					mCollisionsToHandle.push_back(mCollisionSprites1);
					mSpritesToDraw.clear();
					mSpritesToDraw.push_back(mSpritesMap0);
					mSpritesToDraw.push_back(mSpritesMap1);
					break;
				case 1:
					this->createLevel(mCollisionSprites2, mSpritesMap2, mLevel);
					mCollisionsToHandle.clear();
					mCollisionsToHandle.push_back(mCollisionSprites1);
					mCollisionsToHandle.push_back(mCollisionSprites2);
					mSpritesToDraw.clear();
					mSpritesToDraw.push_back(mSpritesMap1);
					mSpritesToDraw.push_back(mSpritesMap2);

					break;
				case 2:
					this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel);
					mCollisionsToHandle.clear();
					mCollisionsToHandle.push_back(mCollisionSprites2);
					mCollisionsToHandle.push_back(mCollisionSprites0);
					mSpritesToDraw.clear();
					mSpritesToDraw.push_back(mSpritesMap2);
					mSpritesToDraw.push_back(mSpritesMap0);
					break;
				}
				++mapCounter;
	}
		
}

void 
TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;


			for (std::vector<int>::size_type i = 0; i != mSpritesToDraw.size(); i++) 
			{
				for (std::vector<int>::size_type j = 0; j != mSpritesToDraw[i].size(); j++) 
				{
				
					target.draw(mSpritesToDraw[i][j].getSpriteToDraw());
				}


			}

}


std::vector<std::vector<Tile>>&
TileMap::getCollisionSprites() 
{
	return this->mCollisionsToHandle;
}