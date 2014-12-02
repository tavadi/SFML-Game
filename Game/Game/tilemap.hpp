#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <stdlib.h>     /* srand, rand */
#include "TextureManager.hpp"
#include "Tile.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Vector2u size);
	~TileMap();
	void CreateLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<Tile>& getCollisionSprites();


private:
	void populateArr(int* level);

	sf::Vector2u mWindowSize;
	TextureManager mTextureManager;
	std::vector<Tile> mSpritesToDraw;
	std::vector<Tile> mCollisionSprites;
	unsigned int mMapHeight;
	unsigned int mMapWidth;
	float mTexturePosX;
	float mTexturePosY;
	float mTexuteSize;
	int mapCount;
	unsigned int noCollisionCount;
	int* mLevel;
};


#endif // TILEMAP_HPP