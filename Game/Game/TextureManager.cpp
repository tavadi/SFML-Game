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
		std::cout << "Could not load TileSet" << std::endl;
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



	subRect.left = 16;
	subRect.top = 0;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["WallL"] = sprite;


	subRect.left = 32;
	subRect.top = 0;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["WallR"] = sprite;


	//----------------------------------
	subRect.left = 0;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerUp1"] = sprite;	

	subRect.left = 16;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerUp2"] = sprite;

	subRect.left = 32;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerUp3"] = sprite;


	//----------------------------------

	subRect.left = 0;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerDown1"] = sprite;

	subRect.left = 16;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerDown2"] = sprite;
	
	subRect.left = 32;
	subRect.top = 32;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerDown3"] = sprite;

	//----------------------------------

	subRect.left = 0;
	subRect.top = 48;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerRight1"] = sprite;

	subRect.left = 16;
	subRect.top = 48;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerRight2"] = sprite;

	subRect.left = 32;
	subRect.top = 48;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerRight3"] = sprite;


	//----------------------------------

	subRect.left = 0;
	subRect.top = 64;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerLeft1"] = sprite;

	subRect.left = 16;
	subRect.top = 64;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerLeft2"] = sprite;

	subRect.left = 32;
	subRect.top = 64;
	sprite.setTextureRect(subRect);
	this->mTileSpirtes["PlayerLeft3"] = sprite;


	return true;
}



sf::Sprite& TextureManager::getSpriteRef(const std::string& Sprite)
{
	return this->mTileSpirtes.at(Sprite);
}



std::map<std::string, sf::Sprite> TextureManager::getTiles() const
{
	return this->mTileSpirtes;
}
