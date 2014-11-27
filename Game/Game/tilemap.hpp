#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TextureManager.hpp"
#include "Tile.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Vector2u size);
	~TileMap();
	void CreateLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<Tile> getCollisionSprites() const;


private:
	sf::Vector2u mWindowSize;
	TextureManager mTextureManager;
	std::vector<Tile> mSpritesToDraw;
	std::vector<Tile> mCollisionSprites;
};


#endif // TILEMAP_HPP