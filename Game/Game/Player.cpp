#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, anim(texturemanager)
{
	anim.loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	anim.loadAnimations(mAnimationSpritesProjectile, "Projectile", 3);
	this->mGameObjectSprite = &mAnimationSpritesUp[0];
}



Player::~Player()
{
	
}



void Player::update(sf::Time timeSinceLastUpdate,PlayerStats stats)
{
	
	mElapsedTime += timeSinceLastUpdate;
	static int UpSideAnimCounter = 1;
	
	//Movement
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
			this->mGameObjectSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			mElapsedTime -= sf::seconds(0.20f);
		}
	}
	mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());

	//Shooting
	static sf::Time shootElapsedTime;
	shootElapsedTime += timeSinceLastUpdate;
	if (stats.isShooting == true && shootElapsedTime >= sf::seconds(0.5f))
	{
		this->shoot(timeSinceLastUpdate);
		shootElapsedTime -= shootElapsedTime;
		sf::Vector2f pos(this->getPosition());
		Projectile p(mTexutureManager.getSpriteRef("Projectile1"), -800.0f, pos);
		mProjectiles.push_back(p);
	}


	for (std::vector<int>::size_type i = 0; i != mProjectiles.size(); ++i)
	{
		mProjectiles[i].update(timeSinceLastUpdate);
	}

}


void Player::shoot(sf::Time elapsedTime)
{
	//Projectile p(mAnimationSpritesProjectile, 10.0f,this->getPosition());
	

}


std::vector<Projectile> Player::getProjectiles()
{
	return this->mProjectiles;
}