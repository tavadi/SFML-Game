#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TextureManager.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Vector2u size);
	~TileMap();
	void CreateLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<sf::Sprite> getCollisionSprites() const;

private:
	sf::Vector2u mWindowSize;
	TextureManager mTextureManager;
	std::vector<sf::Sprite> mSpritesToDraw;
	std::vector<sf::Sprite> mCollisionSprites;
};


#endif // TILEMAP_HPP