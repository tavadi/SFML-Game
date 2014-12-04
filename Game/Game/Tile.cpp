#include "Tile.hpp"

Tile::Tile(){



}

Tile::Tile(sf::Sprite sprite, std::string type)
	:mTileSprite(sprite)
	, mTileType(type)
{
	


}


Tile::~Tile(){


}


std::string Tile::getTileType() const
{
	return this->mTileType;
}

void Tile::setTileType(const std::string type)
{
	this->mTileType = type;
}

void Tile::setSprite(sf::Sprite sprite)
{
	this->mTileSprite = sprite;
}

sf::Sprite Tile::getSpriteToDraw() const {
		return mTileSprite;
}


sf::Sprite& Tile::getSpriteRef()
{
	return this->mTileSprite;
}


