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
	, mMapCounter(0)
	, mTextureManager(texturemanager)
	, mNoCollisionCount(0)
	, mHasStarted(false)
	, mCamPos(0)
{
	//std::cout << "2 : TileMap Created" << std::endl;
	this->populateArr(mLevel0);
	this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel0);
	mSpritesToDraw.push_back(mSpritesMap0);
	mCollisionsToHandle.push_back(mCollisionSprites0);
}


TileMap::~TileMap()
{
	//delete[] mLevel0;
	//delete[] mLevel1;
	//delete[] mLevel2;
}




void TileMap::populateArr(int* level)
{
	//basic random map gen, needs rework
	//std::cout << std::endl;
	////std::cout << "Append TileMap:" << std::endl;
	int noCollisionCount = 0;
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
			int rand1 = rand() % 6 + 3;
			int randN = rand() % 8 + rand1;
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

	}
	int rand1 = rand() % mTileMapCount + 1;


	if (rand1 % mMapWidth == 0 || rand1 % mMapWidth == 8)
	{
		rand1++;
		
	}
	//std::cout << "POS: " << rand1 << std::cout;
	//std::cout << "POS : " << rand1 << std::endl;
	level[rand1] = 5; // SpeedPowerUp



	 rand1 = rand() % mTileMapCount + 1;
	if (rand1 % mMapWidth == 0 || rand1 % mMapWidth == 8)
	{
		rand1++;
	}
	int rand2 = rand() % 2 + 1;
	if (rand2 == 2)
	{
		/*std::cout << "rand2: " << rand2 <<"rand1" << rand1 <<  std::endl;*/
		level[rand1] = 6; // shield
	}
	
	//std::cout << std::endl;
}

void TileMap::createLevel(std::vector<Tile>& Collisionmap, std::vector<Tile>& drawMap, int *level)
{
	Collisionmap.clear();
	drawMap.clear();
	mNoCollisionCount = 0;
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
				++mNoCollisionCount;
				drawMap.push_back(tempSprite);
				break;
			case 1:
				tempSprite.setSprite(mTextureManager.getSpriteRef("Ice2"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.setTileType("Ice");
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				++mNoCollisionCount;
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
			case 5:
				tempSprite.setSprite(mTextureManager.getSpriteRef("SpeedPowerUp"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				tempSprite.setTileType("SpeedPowerUp");
				Collisionmap.push_back(tempSprite);
				break;
			case 6:
				tempSprite.setSprite(mTextureManager.getSpriteRef("ShieldPowerUp"));
				tempSprite.getSpriteRef().setScale(5.0f, 5.0f);
				tempSprite.getSpriteRef().setPosition(mTexturePosX, mTexturePosY);
				tempSprite.setTileType("ShieldPowerUp");
				Collisionmap.push_back(tempSprite);
				break;
			}
			mTexturePosX += mTexuteSize;
		}
		mTexturePosX = 0;
		mTexturePosY -= mTexuteSize;
	}
	//drawMap.insert(drawMap.end(), Collisionmap.begin(),Collisionmap.end());
}

void TileMap::updateTile(size_t i, size_t j, const std::string tileType)
{
	mCollisionsToHandle[i][j].setTileType(tileType);
	mCollisionsToHandle[i][j].setSprite(mTextureManager.getSpriteRef("Ice1"));
	
	//if (mMapCounter == 3)
	//{
	//	mMapCounter = 0;
	//}
	

	switch (mMapCounter)
	{
		
	case 0:
		if (i == 0)
		{
			mCollisionSprites0[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		else
		{
			mCollisionSprites2[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		
		break;
	case 1:
		if (i == 0)
		{
			mCollisionSprites0[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		else
		{
			mCollisionSprites1[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		break;
	case 2:
		if (i == 0)
		{
			mCollisionSprites1[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		else
		{
			mCollisionSprites2[j].setSprite(mTextureManager.getSpriteRef("Ice1"));
		}
		break;
	}
}


//Problem: es werden immer zwei maps eingefügt, eine neue und eine alte, die alte ist nicht die geupdatete demnach erscheinen
//zerstörte tiles wieder
bool TileMap::updateTileMap(float camPosY, float cameraSpeed)
{
	//std::cout << "CUrrent MAP: " << mMapCounter << std::endl;

	mCamPosition += cameraSpeed;
	//std::cout << camPosition << std::endl;
	//if (fmod(camPosY, 800) == 0 && camPosY != 0)
	if (mCamPosition <= -790)
	{
		//std::cout << camPosY << std::endl;
		if (mMapCounter == 3)
		{
			mMapCounter = 0;
		}
		//std::cout << "Delete: mCollisionSprites [" << mMapCounter << "], Create: On top Position  mCollisionSprites[" << mMapCounter << "]" << std::endl;
		switch (mMapCounter)
		{
			//note inefficent Because vectors use an array as their underlying storage,
			//erasing elements in positions other than the vector end causes the container 
			//to relocate all the elements after the segment erased to their new positions. 
			//TODO : write efficently!
		case 0:
			this->populateArr(mLevel1);
			this->createLevel(mCollisionSprites1, mSpritesMap1, mLevel1);
			if (mHasStarted == true)
			{
				mCollisionsToHandle.erase(mCollisionsToHandle.begin());
				mCollisionsToHandle.push_back(mCollisionSprites1);
				mSpritesToDraw.erase(mSpritesToDraw.begin());
				mSpritesToDraw.push_back(mSpritesMap1);
			}
			else
			{
				mCollisionsToHandle.push_back(mCollisionSprites1);
				mSpritesToDraw.push_back(mSpritesMap1);
				mHasStarted = true;
			}
			break;
		case 1:
			this->populateArr(mLevel2);
			this->createLevel(mCollisionSprites2, mSpritesMap2, mLevel2);
			mCollisionsToHandle.erase(mCollisionsToHandle.begin());
			mCollisionsToHandle.push_back(mCollisionSprites2);
			mSpritesToDraw.erase(mSpritesToDraw.begin());
			mSpritesToDraw.push_back(mSpritesMap2);
			break;
		case 2:
			this->populateArr(mLevel0);
			this->createLevel(mCollisionSprites0, mSpritesMap0, mLevel0);
			mCollisionsToHandle.erase(mCollisionsToHandle.begin());
			mCollisionsToHandle.push_back(mCollisionSprites0);
			mSpritesToDraw.erase(mSpritesToDraw.begin());
			mSpritesToDraw.push_back(mSpritesMap0);
			break;
		}
		mCamPosition = 0;
		++mMapCounter;
		return true;
	}
	return false;
}



std::vector<std::vector<Tile>>& TileMap::getCollisionSprites()
{
	return this->mCollisionsToHandle;
}





std::vector<std::vector<Tile>>& TileMap::getSpritesToDraw()
{
	return this->mSpritesToDraw;
}