#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
{
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp1"));
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp2"));
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp3"));
	
	for (size_t i = 0; i < mAnimationSpritesUp.size(); ++i)
	{
		mAnimationSpritesUp[i].setScale(3.0f, 3.0f);
	}
	this->mPlayerSprite = &mAnimationSpritesUp[0];

}



Player::~Player()
{
	
}

//TODO: FIX: figur bewegt sich nicht weil die jeweiligen sprites ihre eigene position haben

void Player::animateSpirte(sf::Time timeSinceLastUpdate,PlayerStats stats)
{
	mElapsedTime += timeSinceLastUpdate;
	static int UpSideAnimCounter = 1;
	if (stats.mIsMovingUp == true)
	{
		if (mCurrentAnimSprite == 2){
			UpSideAnimCounter = -1;
		}
		else
			if (mCurrentAnimSprite == 0)
			{
			UpSideAnimCounter = 1;
			}

		if (mElapsedTime >= sf::seconds(0.2f))
		{
			mCurrentAnimSprite += UpSideAnimCounter;
			this->mPlayerSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			mElapsedTime -= sf::seconds(0.2f);
		}
	}


	mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());
}

sf::Sprite Player::getSpriteRef()
{
	return *mPlayerSprite;
}

