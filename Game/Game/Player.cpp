#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
{
	//mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp1"));
	//mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp2"));
	//mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp3"));
	//
	//for (size_t i = 0; i < mAnimationSpritesUp.size(); ++i)
	//{
	//	mAnimationSpritesUp[i].setScale(3.0f, 3.0f);
	//}
	loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	loadAnimations(mAnimationSpritesRight, "PlayerRight", 3);
	loadAnimations(mAnimationSpritesLeft, "PlayerLeft", 3);
	loadAnimations(mAnimationSpritesDown, "PlayerDown", 3);
	this->mPlayerSprite = &mAnimationSpritesUp[0];

}

void Player::loadAnimations(std::vector<sf::Sprite>& animVec,const std::string& animName,const size_t animCount)
{
	for (size_t i = 1; i < animCount + 1; ++i)
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

//TODO: FIX: figur bewegt sich nicht weil die jeweiligen sprites ihre eigene position haben

void Player::animateSpirte(sf::Time timeSinceLastUpdate,PlayerStats stats)
{
	mElapsedTime += timeSinceLastUpdate;
	static int UpSideAnimCounter = 1;
	

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
			
		
			if (stats.mIsMovingLeft == true)
			{
				this->mPlayerSprite = &mAnimationSpritesLeft[mCurrentAnimSprite];
			}
			else if (stats.mIsMovingRight == true)
			{
				this->mPlayerSprite = &mAnimationSpritesRight[mCurrentAnimSprite];
			}
			else if (stats.mIsMovingUp == true)
			{
				this->mPlayerSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			}
			else if (stats.mIsMovingDown == true)
			{
				this->mPlayerSprite = &mAnimationSpritesDown[mCurrentAnimSprite];
			}
			
			mElapsedTime -= sf::seconds(0.2f);
		}
		mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());
		mAnimationSpritesDown[mCurrentAnimSprite].setPosition(this->getPosition());
		mAnimationSpritesRight[mCurrentAnimSprite].setPosition(this->getPosition());
		mAnimationSpritesLeft[mCurrentAnimSprite].setPosition(this->getPosition());

	
}

sf::Sprite Player::getSpriteRef()
{
	return *mPlayerSprite;
}

