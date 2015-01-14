#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, anim(texturemanager)
	, mPlayerHealth(30)
	, mHealthCounter(3)
{
	anim.loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	anim.loadAnimations(mAnimationSpritesProjectile, "Projectile", 3);
	this->mGameObjectSprite = &mAnimationSpritesUp[0];
	shootRate += sf::seconds(2.0f);
	shootLength += sf::seconds(0.8f);
	shootElapsedTime = shootRate;
	animationRate += sf::seconds(0.20f);
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
		if (mElapsedTime >= animationRate)
		{
			mCurrentAnimSprite += UpSideAnimCounter;
			this->mGameObjectSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			mElapsedTime -= animationRate;
		}
	}
	unsigned int healthLife = mHealthCounter *85;
	if (healthLife > 255)
	{
		healthLife = 255;
	}
	mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());
	mAnimationSpritesUp[mCurrentAnimSprite].setColor(sf::Color(255, healthLife, healthLife, 255));

/*		
	mPlayer1->getSpriteRef().setColor();*/
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
	mHealthCounter--;
}


void Player::addHealth(int health)
{
	if (mHealthCounter != 5)
	{
		mPlayerHealth += health;
		mHealthCounter++;
	}

}

int Player::getHealth()
{
	return mPlayerHealth;
	if (mHealthCounter != 0){ 
		mHealthCounter--; }
}

void Player::speedUp()
{
	if (animationRate > sf::seconds(0.08f))
	{
		animationRate -= sf::seconds(0.02f);
	}
	
}