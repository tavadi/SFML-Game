#include "TileMap.hpp"


TileMap::TileMap(sf::Vector2u size, TextureManager& texturemanager)
	:mWindowSize(size)
	, mMapHeight(10)
	, mMapWidth(8)
	, mTexturePosX(0)
	, mTexturePosY(-400)
	, mTexuteSize(80)
	, mTileMapCount(mMapHeight*mMapWidth)
	, mLevel0(new int[mTileMapCount])
	, mLevel1(new int[mTileMapCount])
	, mLevel2(new int[mTileMapCount])
	, noCollisionCount(1)
	, mMapCounter(0)
	, mTextureManager(texturemanager)
{
	std::cout << "2 : TileMap Created" << std::endl;
	this->populateArr(mLevel0);
	this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel0);
	mSpritesToDraw.push_back(mSpritesMap0);
	mCollisionsToHandle.push_back(mCollisionSprites0);
}


TileMap::~TileMap()
{
	delete[] mLevel0;
	delete[] mLevel1;
	delete[] mLevel2;
}




void TileMap::populateArr(int* level)
{
	//basic random map gen, needs rework
	std::cout << std::endl;
	std::cout << "Append TileMap:" << std::endl;
	for (int i = 0; i < mTileMapCount; ++i)
	{
		if (i % mMapWidth == 0)
		{
			level[i] = 3;
		}
		else if (i % mMapWidth == 7)
		{
			level[i] = 4;
		}
		else
		{
			int randN = rand() % 8 + 5;
			if (noCollisionCount < randN)
			{
				int randN = rand() % 2;
				level[i] = 0 + randN;
				noCollisionCount++;
			}
			else
			{
				level[i] = 2;
				noCollisionCount = 0;
			}
		}
		std::cout << level[i];
		if (i % mMapWidth == 7)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void TileMap::createLevel(std::vector<Tile>& Collisionmap, std::vector<Tile>& drawMap, int *level)
{
	Collisionmap.clear();
	drawMap.clear();
	for (unsigned int i = 0; i < mMapHeight; ++i)
	{
		for (unsigned int j = 0; j < mMapWidth; ++j)
		{
			Tile tempSprite;
			switch (level[drawMap.size() + Collisionmap.size()])
			{
			case 0:
				tempSprite.setSprite(mTextureManager.getSpriteRef("Ice1"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.setTileType("Ice");
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				drawMap.push_back(tempSprite);
				break;
			case 1:
				tempSprite.setSprite(mTextureManager.getSpriteRef("Ice2"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.setTileType("Ice");
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				drawMap.push_back(tempSprite);
				break;
			case 2:
				tempSprite.setSprite(mTextureManager.getSpriteRef("Wall1"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				tempSprite.setTileType("Wall");
				Collisionmap.push_back(tempSprite);
				break;

			case 3:
				tempSprite.setSprite(mTextureManager.getSpriteRef("WallL"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				tempSprite.setTileType("Wall");
				Collisionmap.push_back(tempSprite);
				break;
			case 4:
				tempSprite.setSprite(mTextureManager.getSpriteRef("WallR"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				tempSprite.setTileType("Wall");
				Collisionmap.push_back(tempSprite);
				break;
			}
			
			mTexturePosX += mTexuteSize;
		}
		mTexturePosX = 0;
		mTexturePosY -= mTexuteSize;
	}
}

void TileMap::updateTile(size_t i, size_t j, const std::string tileType)
{
	mCollisionsToHandle[i][j].setTileType(tileType);
	mCollisionsToHandle[i][j].setSprite(mTextureManager.getSpriteRef("Ice1"));
}


//Problem: es werden immer zwei maps eingefügt, eine neue und eine alte, die alte ist nicht die geupdatete demnach erscheinen
//zerstörte tiles wieder
void TileMap::updateTileMap(float camPosY)
{

	if (fmod(camPosY, 800) == 0 && camPosY != 0)
	{
		std::cout << camPosY << std::endl;
		if (mMapCounter == 3)
		{
			mMapCounter = 0;
		}
		std::cout << "Delete: mCollisionSprites [" << mMapCounter << "], Create: On top Position  mCollisionSprites[" << mMapCounter << "]" << std::endl;
		switch (mMapCounter)
		{
		case 0:
			this->populateArr(mLevel1);
			this->createLevel(mCollisionSprites1, mSpritesMap1, mLevel1);
			mCollisionsToHandle.clear();
			mCollisionsToHandle.push_back(mCollisionSprites0);
			mCollisionsToHandle.push_back(mCollisionSprites1);
			mSpritesToDraw.clear();
			mSpritesToDraw.push_back(mSpritesMap0);
			mSpritesToDraw.push_back(mSpritesMap1);
			break;
		case 1:
			this->populateArr(mLevel2);
			this->createLevel(mCollisionSprites2, mSpritesMap2, mLevel2);
			mCollisionsToHandle.clear();
			mCollisionsToHandle.push_back(mCollisionSprites1);
			mCollisionsToHandle.push_back(mCollisionSprites2);
			mSpritesToDraw.clear();
			mSpritesToDraw.push_back(mSpritesMap1);
			mSpritesToDraw.push_back(mSpritesMap2);

			break;
		case 2:
			this->populateArr(mLevel0);
			this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel0);
			mCollisionsToHandle.clear();
			mCollisionsToHandle.push_back(mCollisionSprites2);
			mCollisionsToHandle.push_back(mCollisionSprites0);
			mSpritesToDraw.clear();
			mSpritesToDraw.push_back(mSpritesMap2);
			mSpritesToDraw.push_back(mSpritesMap0);
			break;
		}
		++mMapCounter;
	}

}



std::vector<std::vector<Tile>>& TileMap::getCollisionSprites()
{
	return this->mCollisionsToHandle;
}





std::vector<std::vector<Tile>>& TileMap::getSpritesToDraw()
{
	return this->mSpritesToDraw;
}