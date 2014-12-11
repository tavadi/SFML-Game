#include "player.hpp"

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
{
	mAnimationSpritesUp.push_back(mTexutureManager.getRef("PlayerUp1"));
	mAnimationSpritesUp.push_back(mTexutureManager.getRef("PlayerUp2"));
	mAnimationSpritesUp.push_back(mTexutureManager.getRef("PlayerUp3"));
	this->mPlayerSprite = mAnimationSpritesUp[0];

}



Player::~Player()
{
	
}


void Player::animateSpirte(sf::Time timeSinceLastUpdate)
{
	mElapsedTime += timeSinceLastUpdate;
	if (mCurrentAnimSprite >= 2){
		mCurrentAnimSprite = 0;
	}

	if (mElapsedTime >= sf::seconds(1.0f))
	{
		++mCurrentAnimSprite;
		this->mPlayerSprite.setTexture = mAnimationSpritesUp[mCurrentAnimSprite];
		mElapsedTime -= sf::seconds(1.0f);
		
	}
}

sf::Sprite& Player::getSpriteRef()
{
	return this->mPlayerSprite;
}

