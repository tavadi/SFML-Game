#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, anim(texturemanager)
{
	anim.loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	anim.loadAnimations(mAnimationSpritesRight, "PlayerRight", 3);
	anim.loadAnimations(mAnimationSpritesLeft, "PlayerLeft", 3);
	anim.loadAnimations(mAnimationSpritesDown, "PlayerDown", 3);
	this->mPlayerSprite = &mAnimationSpritesUp[0];
}

void Player::loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t numberofSprites)
{
	for (size_t i = 1; i < numberofSprites + 1; ++i)
	{
		std::string tempString = animName + std::to_string(i);
		sf::Sprite tempSprite = mTexutureManager.getSpriteRef(tempString);
		tempSprite.setScale(3.0f, 3.0f);
		animVec.push_back(tempSprite);
	}

}

Player::~Player()
{
	
}


void Player::shoot(sf::Time timeSinceLastUpdate, projectile projectile)
{


}

//TODO: FIX: figur bewegt sich nicht weil die jeweiligen sprites ihre eigene position haben

void Player::animateSpirte(sf::Time timeSinceLastUpdate,PlayerStats stats)
{
	mElapsedTime += timeSinceLastUpdate;
	static int UpSideAnimCounter = 1;
	
	if (stats.isAlive == true && 
		(stats.mIsMovingDown == true ||
		stats.mIsMovingLeft == true ||
		stats.mIsMovingUp == true ||
		stats.mIsMovingRight == true))
	{
		if (mCurrentAnimSprite == 2){
			UpSideAnimCounter = -1;
		}
		else if (mCurrentAnimSprite == 0)
		{
			UpSideAnimCounter = 1;
		}
		if (mElapsedTime >= sf::seconds(0.20f))
		{
			mCurrentAnimSprite += UpSideAnimCounter;
			this->mPlayerSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			mElapsedTime -= sf::seconds(0.20f);
		}
	}
		
		mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());

	
}



sf::Sprite Player::getSpriteRef()
{
	return *mPlayerSprite;
}

