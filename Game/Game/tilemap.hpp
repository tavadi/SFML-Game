#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include "TextureManager.hpp"
#include "Tile.hpp"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <math.h>  


class TileMap
{
public:
	TileMap(sf::Vector2u size, TextureManager& txtmanager);
	~TileMap();
	void createLevel(std::vector<Tile>& collisionMap, std::vector<Tile>& drawMap, int *level);
	void updateTileMap(float camPosY);
	std::vector<std::vector<Tile>>& getCollisionSprites();
	std::vector<std::vector<Tile>>& getSpritesToDraw();
	void updateTile(size_t i, size_t j, const std::string tileType);

private:
	void populateArr(int* level);
	sf::Vector2u mWindowSize;
	
	sf::Time mTileMapUpdateTime;

	std::vector<std::vector<Tile>> mSpritesToDraw;
	std::vector<Tile> mSpritesMap0;
	std::vector<Tile> mSpritesMap1;
	std::vector<Tile> mSpritesMap2;
	std::vector<Tile> mCollisionSprites0;
	std::vector<Tile> mCollisionSprites1;
	std::vector<Tile> mCollisionSprites2;
	std::vector<std::vector<Tile>> mCollisionsToHandle;

	unsigned int mMapCounter;
	float mTexuteSize;
	unsigned int mMapHeight;
	unsigned int mMapWidth;
	float mTexturePosX;
	float mTexturePosY;
	int mTileMapCount;
	float mCamPos;

	//for populateArr function/rand
	
	int* mLevel0;
	size_t mNoCollisionCount;
	int* mLevel1;
	int* mLevel2; 

	//INFO how many tiles there are that are not needed to check for collision detection
	
	TextureManager mTextureManager;
};


#endif // TILEMAP_HPP