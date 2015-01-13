#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, anim(texturemanager)
	, mPlayerHealth(50)
{
	anim.loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	anim.loadAnimations(mAnimationSpritesProjectile, "Projectile", 3);
	this->mGameObjectSprite = &mAnimationSpritesUp[0];
	shootRate += sf::seconds(2.0f);
	shootLength += sf::seconds(0.3f);
	shootElapsedTime = shootRate;
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
	 
	shootElapsedTime += timeSinceLastUpdate;

	if (shootElapsedTime >= shootLength && !mProjectiles.empty())
	{
			mProjectiles.erase(mProjectiles.begin());
	}

	if (stats.isShooting == true && shootElapsedTime >= shootRate)
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


std::vector<Projectile>& Player::getProjectiles()
{
	return this->mProjectiles;
}


void Player::removeProjectile(float i)
{
	mProjectiles.erase(mProjectiles.begin() + i);

}


void Player::removeHealth(int damage)
{
	mPlayerHealth -= damage;
}


void Player::addHealth(int health)
{
	mPlayerHealth += health;
}

int Player::getHealth()
{
	return mPlayerHealth;
}