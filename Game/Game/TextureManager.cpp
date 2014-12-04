#include "TextureManager.hpp"
#include "Collision.h"


TextureManager::TextureManager()
{
	this->LoadTextures();

}


TextureManager::~TextureManager()
{


}


bool TextureManager::LoadTextures()
{
	if (!Collision::CreateTextureAndBitmask(mTileSet, "tileset.png"))
	{
		std::cout << "could not load TileSet" << std::endl;
		return false;
	}

	sf::IntRect subRect;
	subRect.left = 0;
	subRect.top = 0;
	subRect.width = 16;
	subRect.height = 16;
	sf::Sprite sprite(mTileSet, subRect);
	this->mTileSpirtes["Wall1"] = sprite;


	subRect.left = 0;
	subRect.top = 16;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["Ice1"] = sprite;


	subRect.left = 16;
	subRect.top = 16;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["Ice2"] = sprite;

	return true;
}



sf::Sprite& TextureManager::getRef(const std::string& texture)
{
	return this->mTileSpirtes.at(texture);
}



std::map<std::string, sf::Sprite> TextureManager::getTiles() const
{
	return this->mTileSpirtes;
}
