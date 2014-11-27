
#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile 
{
public:
	Tile::Tile();
	Tile::Tile(sf::Sprite sprite, std::string type);
	Tile::~Tile();
	std::string getTileType() const;
	void setSprite(sf::Sprite sprite);
	void setTileType(const std::string type);
	sf::Sprite getSpriteToDraw() const;
	sf::Sprite& getSpriteRef();
private:
	sf::Sprite mTileSprite;
	std::string mTileType;

};



#endif // TILE_HPP