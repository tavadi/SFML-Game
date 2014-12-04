#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include "TextureManager.hpp"
#include "Tile.hpp"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <math.h>  


class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Vector2u size);
	~TileMap();
	void createLevel(std::vector<Tile>& collisionMap, std::vector<Tile>& drawMap, int *level);
	void updateTileMap(float camPosY);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<std::vector<Tile>>& getCollisionSprites();

private:
	void populateArr(int* level);
	sf::Vector2u mWindowSize;
	TextureManager mTextureManager;
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
	int noCollisionCount;
	int* mLevel0;
	int* mLevel1;
	int* mLevel2;
};


#endif // TILEMAP_HPP